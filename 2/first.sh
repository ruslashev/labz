#!/bin/zsh

cat <<EOF
Enter your choice:
1) Print full working directory path
2) List directory contents
3) Log out
4) Cancel
EOF

while echo -n "> "; read choice; do
	case $choice in
		[1] )
			pwd
			break;;
		[2] )
			ls
			break;;
		[3] )
			logout
			break;;
		[4] )
			break;;
		* )
			echo "Invalid option. Please enter your choice as '1' etc.";;
	esac
done

