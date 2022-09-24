/*
http://www.jikos.cz/jikos/Kmalloc_Internals.html
https://ruffell.nz/programming/writeups/2019/02/15/looking-at-kmalloc-and-the-slub-memory-allocator.html

The general process for SLAB is this:

The kernel is asked for memory for an object of size x
The SLAB allocator looks in the slab index for the slab that holds objects of size x
The SLAB allocator gets a pointer to the slab where objects are stored
The SLAB allocator finds the first place with an empty slot
The SLAB allocator returns the address of the empty slot, with some housekeeping to do on the side.
*/

// kmalloc() is defined in /include/linux/slab.h:446

static __always_inline void *kmalloc(size_t size, gfp_t flags)
{
	if (__builtin_constant_p(size)) {
		if (size > KMALLOC_MAX_CACHE_SIZE)
			return kmalloc_large(size, flags);
#ifndef CONFIG_SLOB
		if (!(flags & GFP_DMA)) {
			int index = kmalloc_index(size);

			if (!index)
				return ZERO_SIZE_PTR;

			return kmem_cache_alloc_trace(kmalloc_caches[index],
					flags, size);
		}
#endif
	}
	return __kmalloc(size, flags);
}

// __kmalloc() is defined in /mm/slub.c:3519
// The "struct kmem_cache" contains a list of the active slabs, and ret will be the object that we will be returning.
void *__kmalloc(size_t size, gfp_t flags)
{
	struct kmem_cache *s;
	void *ret;

	if (unlikely(size > KMALLOC_MAX_CACHE_SIZE))
		return kmalloc_large(size, flags);

	s = kmalloc_slab(size, flags);

	if (unlikely(ZERO_OR_NULL_PTR(s)))
		return s;

	ret = slab_alloc(s, flags, _RET_IP_);

	trace_kmalloc(_RET_IP_, ret, size, s->size, flags);

	kasan_kmalloc(s, ret, size);

	return ret;
}
