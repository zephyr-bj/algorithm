package main
// the namespace restricted what we can see from the container

// new hostname
// new process id list
// own version of /proc of the directory
// new root directory (where the file "ROOT_FOR_XXX" is contained)
// mount the new proc file system

// the cgroup limits the resource system that we can use

// filesystem interface
//	memory
//	CPU
//	IO
//	process numbers
//
// /sys/fs/cgroup
// take the example of memory, there are lot of attributes, such as:
// 	/sys/fs/cgroup/memory/memory.limit_in_bytes
// we can also see a directory for docker
// 	/sys/fs/cgroup/memory/docker, witch contains all the same files as /sys/fs/cgroup/memory
// after we run "# docker run --rm -it ubuntu /bin/bash",
//	there is new directory in /sys/fs/cgroup/memory/docker/xxxx, where xxxx is the container ID
//	docker create a control group of the container, but "/sys/fs/cgroup/memory/docker/xxxx/memory.limit_in_bytes" same as "/sys/fs/cgroup/memory/memory.limit_in_bytes"
// after we run "# docker run --rm -it --memory=10M ubuntu /bin/bash"
// 	"/sys/fs/cgroup/memory/docker/xxxx/memory.limit_in_bytes" shows 10M in bytes


// bash script recursively call itself ":() { : | : & }; :", creating processes forever
// we define a function called ":()" 
// in that function, we call ":" and pipe the result into ":", which we running in the back ground "{ : | : & };"
// then we invoke the function ":" ==> ":() { : | : & }; :", it calling itself creating/forking processes forever

import (
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"syscall"
)
// docker         run image <cmd> <args>
// go run main.go run       <cmd> <args>
func main() {
	switch os.Args[1] {
	case "run":
		run()
	case "child":
		child()
	default:
		panic("help")
	}
}

func run() {
	fmt.Printf("Running %v \n", os.Args[2:])
        // run an arbitary command
	// # go run main.go run echo hello Amsterdam
	// # go run main.go run /bin/bash
	// "/proc/self/exe": reinvoke the process inside the new namespace
	cmd := exec.Command("/proc/self/exe", append([]string{"child"}, os.Args[2:]...)...)
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	// create namespace
	// Cloneflags: clone this process to get a new namespace
	// NEWUTS: unix time sharing system, allow us to change the hostname in container without affect the hostname of host
	// NEWPID: new process id
	// NEWNS: new name space
	// Unshareflags: to prevent recursively share between namepaces
	//               I have new namespace in this container, but I don't want to share it with the host
	//               after this, we cannot see the mounted /proc of container in the host
	cmd.SysProcAttr = &syscall.SysProcAttr{
		Cloneflags:   syscall.CLONE_NEWUTS | syscall.CLONE_NEWPID | syscall.CLONE_NEWNS,
		Unshareflags: syscall.CLONE_NEWNS,
	}

	must(cmd.Run())
}

func child() {
	fmt.Printf("Running %v \n", os.Args[2:])
        // se the control group
	cg()

	cmd := exec.Command(os.Args[2], os.Args[3:]...)
	cmd.Stdin = os.Stdin
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
        // set a hostname in the new namespace as "container"
	must(syscall.Sethostname([]byte("container")))
	// change the root directory of the container
	must(syscall.Chroot("/home/liz/ubuntufs"))
	// then change the current directory to the new root
	// after this step, anything up level directory in the host system cannot be seen
	// we can see the container process from the host /proc, and "ls -l" show that, the root of this process is a soft link to the container root
	// => for this process, its root is just the file system we just mounted
	// this is pretty much equavalent to a container image: 
	// => when you specify a image, it takes copy of the file system packed in the image, and unpacked it into somewhere in you host machine and chroot the
	//    container to see the new file system
	must(os.Chdir("/"))
	// mount the proc psudo file system in the container
	must(syscall.Mount("proc", "proc", "proc", 0, ""))
	must(syscall.Mount("thing", "mytemp", "tmpfs", 0, ""))

	must(cmd.Run())

	must(syscall.Unmount("proc", 0))
	must(syscall.Unmount("thing", 0))
}

func cg() {
	cgroups := "/sys/fs/cgroup/"
	// only control pids in this example
	pids := filepath.Join(cgroups, "pids")
	// "liz" is the container liz created
	os.Mkdir(filepath.Join(pids, "liz"), 0755)
	// pids can not more than 20
	must(ioutil.WriteFile(filepath.Join(pids, "liz/pids.max"), []byte("20"), 0700))
	// Removes the new cgroup in place after the container exits
	must(ioutil.WriteFile(filepath.Join(pids, "liz/notify_on_release"), []byte("1"), 0700))
	// this current process (return from Getpid()) is belong to this cgroup which limits the process id max	
	must(ioutil.WriteFile(filepath.Join(pids, "liz/cgroup.procs"), []byte(strconv.Itoa(os.Getpid())), 0700))
}

func must(err error) {
	if err != nil {
		panic(err)
	}
}
