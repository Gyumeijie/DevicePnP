#! /bin/bash

if [[ $# < 2 ]];
then
   echo "usage: bulid.sh input_file output_file"
   exit 1
fi

#set the input and output flle
input=$1
output=$2

#clear the output file first
rm -f $output

#process the input file
awk_stdout=`awk '
   $1 ~ /^[ ]*include/{
    # if the file not exists, the print the filename to stdout
    # which will be caught by the shell runs it
    if (system("test -e " $2)){
       print $2
       exit 1
    }else{
       system("cat " $2 " >> " output_file)
    }
  }

  $1 !~ /^[ ]*include/{
    # $0 should enclosed by double quotes
    system("echo " "\""  $0 "\""  " >> " output_file)
  }' output_file=$output $input`


#check the result
if [[ $awk_stdout != "" ]];
then
    echo "error: file $awk_stdout not exist!"
else
    echo "bulid xml done."
fi
