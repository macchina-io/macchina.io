#! /bin/sh
#
# $Id: //poco/1.4/release/script/verifyspecs.sh#1 $
#
# verifyspecs
#
# Ensure all release specifications are complete.
#
# usage: verifyspecs
#

if [ "$POCO_BASE" = "" ] ; then
  echo "Error: POCO_BASE not set."
  exit 1
fi

if [ "$1" == "-e" ] ; then
  edit=1
fi

customersFile=$POCO_BASE/release/spec/current_customers
while read spec
do
	if [ -f $POCO_BASE/release/spec/${spec}.release ]
	then
		for f in $POCO_BASE/release/spec/packages/*.release
		do
			sort <$f >/tmp/verifyspec.required
			sort <$POCO_BASE/release/spec/${spec}.release >/tmp/verifyspec.have
			reqlines=`wc -l </tmp/verifyspec.required`
			havelines=`comm -12 /tmp/verifyspec.have /tmp/verifyspec.required | wc -l`
			if [ $havelines -ne 0 ] ; then
				if [ $reqlines -ne $havelines ] ; then
					echo "=== Missing files: $spec ==="
					comm -23 /tmp/verifyspec.required /tmp/verifyspec.have
					if [ "$edit" == 1 ] ; then
						p4 edit $POCO_BASE/release/spec/${spec}.release 
						bbedit $POCO_BASE/release/spec/${spec}.release
					fi
				fi
			fi
		done
	else
		echo "Release spec not found: $spec"
	fi
done <$customersFile
