#!/bin/bash
# clear
echo
#asg=asg1

itcourse=IT328
dock=/home/ad.ilstu.edu/cli2/Public/IT328dock

if [  $# -lt 2 ] ; then 
	echo " Error!!"
	echo
	echo " You should provide a secret name and the assignment directory."
	echo " For example, if peekapoo is the secret name and npc is the assignment directory:"
	echo
        echo " bash /home/ad.ilstu.edu/cli2/Public/IT328/submit328.sh peekapoo npc"
	echo
	exit 
fi 

if [ ! -d $HOME/$itcourse/$2 ] ; then 
	echo  " Error!!"
	echo " You haven't created directory $itcourse/$2 and put all your programs in it."
	echo
	exit 
fi 

date >> $dock/log$2
echo "$USER [$1] $2" >> $dock/log$2

if [ ! -d $dock/$USER ] ; then
	mkdir $dock/$USER	
	chmod 733 $dock/$USER 
fi

if [ ! -d $dock/$USER/$1 ] ; then
	mkdir $dock/$USER/$1
	chmod 777 $dock/$USER/$1  
fi

if [ ! -d $dock/$USER/$1/$2 ] ; then
	mkdir $dock/$USER/$1/$2
	chmod 777 $dock/$USER/$1/$2	 
fi

if [ $2 == npc ] ; then #  for assignment 1
	for program in find3SAT.java findVCover.java findClique.java
	do
		if [ ! -f $HOME/$itcourse/$2/$program ] ; then 
			echo  " Error!!"
			echo " Program $program does not exist in $itcourse/$2"
			echo
			exit 
		fi 
	done
else
	echo "The directory name must be npc"
	exit
fi 

#if [ $2 -eq 2 ] ; then #  for assignment 2
#	prog=dijkstra.java
#	if [ ! -f $HOME/$itcourse/asg$2/$prog ] ; then 
#		echo  " Error!!"
#		echo " Program $prog does not exist in $itcourse/asg$2"
#		echo
#		exit 
#	fi 
#fi 

cp -r $HOME/$itcourse/$2/*.java $dock/$USER/$1/$2
chmod -R 777 $dock/$USER/$1/$2
ls -l $dock/$USER/$1/$2
echo "copy files into $dock/$USER/$1/$2"
echo
ls $dock/$USER/$1/$2
echo 
echo "Only Java programs will be copied."
echo "Try ls $dock/$USER/$1/$2 to see if all java files are copied" 
echo

#chmod 755 $HOME
#chmod -R 700 $HOME/$itcourse


