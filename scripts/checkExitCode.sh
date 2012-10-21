#/usr/bin/sh
$2
x=$?
if [ ! $x = $1 ] 
then
	echo "\"$2\" expected to return $1 but return $x"
fi


