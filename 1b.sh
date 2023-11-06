create(){
	echo ""
	echo "--> Enter AddressBook name ::"
	read fname
	echo ""
	
	result=`ls | grep $fname | wc -w`
	
	if [ $result -gt 0 ]
	then
		echo "--> Name already exists."
		echo "Writing into the same!"
	else
		touch $fname
		echo "--> File created successfully!"
		echo ""
	fi
}

insert(){
	result=`ls | grep $fname | wc -w`	
	if [ $result -gt 0 ]
	then
		echo ""
		echo "--> Enter email ::"
		read email
		result=`ls | grep $email | wc -w`
		if [ $result -gt 0 ]
		then
			echo ""
			echo "--> Email already exists!
			Try with different email."
			insert
		else
			echo "--> Enter name :: "
			read name
			echo "--> Enter number :: " 
			read number
			echo ""
			
			record=`echo $email $name $number`
			echo $record >> $fname
			echo "--> Record inserted successfully.
			Do you want to see the inserted data? (y/n)"
			read var1
			if [ $var1 == 'y' ]
			then
				display
			fi
		fi
	else
		echo "--> File doesn't exist.
		Want to create & insert into a new file? (y/n)"
		read var1
		if [ $var1 == 'y' ]
		then
			create
			insert
		fi
	fi
}

display(){
	result=`ls | grep $fname | wc -w`	
	if [ $result -gt 0 ]
	then
		echo ""
		echo "--> RECORDS ::"
		cat $fname
		echo ""
	else
		echo "--> File doesn't exist.
		Want to create & insert into a new file? (y/n)"
		read var1
		if [ $var1 == 'y' ]
		then
			create
			insert
		fi
	fi
}

modify(){
	result=`ls | grep $fname | wc -w`
	if [ $result -gt 0 ]
	then
		echo ""
		echo "--> Enter email ::"
		read email
		result=`cat $fname | grep $email | wc -w`
		if [ $result -gt 0 ]
		then
			echo ""
			echo "--> Update name :: "
			read new_name
			echo "--> Update number :: " 
			read new_number
			echo ""
			
			old=`cat $fname | grep $email`
			echo "OLD RECORD :: $old"
			new=`echo $email $new_name $new_number`
			echo "NEW RECORD :: $new"
			echo ""
			
			sed -i s/"$old"/"$new"/g $fname				# sed - search & replace;
			echo "--> Record modified"				# g - replace globally			
			echo ""		
		else
			echo "--> Email doesn't exist into records.
			Want to insert the email? (y/n)"
			read var1
			if [ $var1 == 'y' ]
			then
				insert
			fi
		fi
	else
		echo "--> File doesn't exist.
		Want to create & insert into a new file? (y/n)"
		read var1
		if [ $var1 == 'y' ]
		then
			create
			insert
		fi
		
	fi
}

delete(){
	result=`ls | grep $fname | wc -w`
	if [ $result -gt 0 ]
	then
		echo ""
		echo "--> Enter email ::"
		read email
		echo ""
		result=`cat $fname | grep $email | wc -w`
		if [ $result -gt 0 ]
		then
			old=`cat $fname | grep $email`
#			sed -i s/"$old"//g $fname			# replace record with empty line
			sed -i /"$old"/d $fname				# delete the empty line
			echo "--> Record DELETED"
			echo ""
		else
			echo "--> Email doesn't exist into records.
			Want to insert the email? (y/n)"
			read var1
			if [ $var1 == 'y' ]
			then
				insert
			fi
		fi
	else
		echo "--> File doesn't exist.
		Want to create & insert into a new file? (y/n)"
		read var1
		if [ $var1 == 'y' ]
		then
			create
			insert
		fi
	fi

}

search(){
	result=`ls | grep $fname | wc -w`
	if [ $result -gt 0 ]
	then
		echo ""
		echo "--> Enter email ::"
		read email
		echo ""
		result=`cat $fname | grep $email | wc -w`
		if [ $result -gt 0 ]
		then
			record=`cat $fname | grep $email`
			echo "--> Record exists!"
			echo $record
		else
			echo "--> Email doesn't exist into records.
			Want to insert the email? (y/n)"
			read var1
			if [ $var1 == 'y' ]
			then
				insert
			fi
		fi
	else
		echo "--> File doesn't exist.
		Want to create & insert into a new file? (y/n)"
		read var1
		if [ $var1 == 'y' ]
		then
			create
			insert
		fi
	fi
}

ch=1
while [ $ch -ne 7 ]
do
	echo ""
	echo "***************** MENU *****************"
	echo "1] Create		2] Display"
	echo "3] Insert record	4] Modify record"
	echo "5] Delete record	6] Search record"
	echo "7] Exit"
	echo "****************************************"
	echo "--> Enter Choice"
	read ch
	echo ""

	case $ch in
		1) create ;;
		2) display ;;
		3) insert ;;
		4) modify ;;
		5) delete ;;
		6) search ;;
		7)	echo "--> EXITING PROGRAM !!" 
			exit ;;
	esac
done




