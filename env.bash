self=$_
if [ $self == $0 ] ; then
	echo "This file must be sourced from bash, not run."
	echo "Usage: . $0"
	exit 1
fi
basedir="$(cd "$(dirname "$self")" ; pwd -P)"
osname=`uname`
osarch=`uname -m`
export MACCHINA_BASE="$basedir"
export MACCHINA_VERSION=`cat $basedir/VERSION`
export PROJECT_BASE="$MACCHINA_BASE"
export POCO_BASE="$MACCHINA_BASE/platform"
if [ $osname = "Darwin" ] ; then
	export DYLD_LIBRARY_PATH=$POCO_BASE/lib/$osname/$osarch:$DYLD_LIBRARY_PATH
	libPath=$DYLD_LIBRARY_PATH
	libPathVar="DYLD_LIBRARY_PATH"
else
	export LD_LIBRARY_PATH=$POCO_BASE/lib/$osname/$osarch:$LD_LIBRARY_PATH
	libPath=$LD_LIBRARY_PATH
	libPathVar="LD_LIBRARY_PATH  "
fi

echo "macchina.io build environment set."
echo ""
echo "\$MACCHINA_BASE     = $MACCHINA_BASE"
echo "\$PROJECT_BASE      = $PROJECT_BASE"
echo "\$POCO_BASE         = $POCO_BASE"
echo "\$MACCHINA_VERSION  = $MACCHINA_VERSION"
echo "\$$libPathVar = $libPath"
echo ""
