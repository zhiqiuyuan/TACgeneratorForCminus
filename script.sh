case_num=6
for((i=1;i<=${case_num};++i))
do
	echo ${i}
	./main test/${i}.cminus
	echo -e "\n"
done
