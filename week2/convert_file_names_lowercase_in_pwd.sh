# For all the files that aren't already in lowercase
for i in $( ls | grep [A-Z] ); 
do
        # rename the file by replacing uppercase letters with lower case letters
        mv -i $i `echo $i | tr 'A-Z' 'a-z'`; 
done
