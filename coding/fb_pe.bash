#[1]#####
# retrieve log/vmstat info and process them
# usage: vmstat -n 1 | ./myscripts.bash in 200 10
#!/bin/bash
awk -v target="$1" -v limit="$2" -v count="$3": '
{
    if($1 == "procs") next;
    if($1 == "r") {
        print "header found" > "/dev/stderr";
        for(i=1; i<NF; i++) {
            header[$i] = i;
        }
        if(header[target] == "") {
            print "target not found" > "/dev/stderr";
            exit;
        }
        next;
    }
    if($header[target] > limit) {
        violation++;
        if(violation > count) print $0;
    }else {
        violation = 0;
    }
}'

#[2]#####
# randomly picking a line from a text file, think about scalability
#!/bin/bash
n=$(awk 'END{print NR}' myscripts.bash)
awk -v line=$n 'BEGIN{srand();x=int(line*rand())};{if(x == NR){ print $0}}' myscripts.bash

#[3]#####
# replace all email address in a html file
#!/bin/bash
sed -E -i 's/[a-zA-Z0-9]+@[a-zA-Z0-9]+\.[a-zA-Z0-9]{2,5}/fake@email\.com/g' emails.html

#[4]#####
# print last n lines from a file
tail -3 file.txt


########
#1. awk format
#awk -v var=x '
#{
#    print something
#}'
#
#2. define a variable: 
#there is no space between variable and "=", nor space between "=" and value
#
#var=$(date)
