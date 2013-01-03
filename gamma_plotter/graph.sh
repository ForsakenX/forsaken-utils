if [[ -z $1 ]]; then
	echo "usage: $0 <gamma value>"
	exit 1
fi
gnuplot -persist <<HERE
plot '-'
`./gamma $1`
HERE
