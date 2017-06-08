#!/bin/zsh

unsetopt function_argzero

usage() {
	echo "Usage: $0 <source> [destination]"
	exit 1
}

cp_or_mv_usage() {
	echo -n "To use Copy or Move commands you need to supply two arguments to "
	echo "the script:\n$ $0 <source> <destination>"
	exit 1
}

rm_usage() {
	echo "Remove command takes exactly one argument:"
	echo "$ $0 <source>"
	exit 1
}

if [[ "$#" -ne 1 ]] && [[ "$#" -ne 2 ]] then
	usage
fi

cat <<EOF
What you want to do with a file:
1) Copy
2) Move
3) Remove
4) Cancel
EOF

while echo -n "> "; read choice; do
	case $choice in
		[1] )
			if [[ "$#" -ne 2 ]] then
				cp_or_mv_usage
			fi
			echo "cp $1 $2"
			# cp "$1" "$2"
			break;;
		[2] )
			if [[ "$#" -ne 2 ]] then
				cp_or_mv_usage
			fi
			echo "mv $1 $2"
			# mv "$1" "$2"
			break;;
		[3] )
			if [[ "$#" -ne 1 ]] then
				rm_usage
			fi
			echo "rm $1"
			# rm "$1"
			break;;
		[4] )
			break;;
		* )
			echo "Invalid option. Please enter your choice as '1' etc.";;
	esac
done

