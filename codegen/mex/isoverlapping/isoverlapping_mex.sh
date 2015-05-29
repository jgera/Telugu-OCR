MATLAB="/Users/venkat/Applications/Applications/MATLAB_R2014a.app"
Arch=maci64
ENTRYPOINT=mexFunction
MAPFILE=$ENTRYPOINT'.map'
PREFDIR="/Users/venkat/.matlab/R2014a"
OPTSFILE_NAME="./mexopts.sh"
. $OPTSFILE_NAME
COMPILER=$CC
. $OPTSFILE_NAME
echo "# Make settings for isoverlapping" > isoverlapping_mex.mki
echo "CC=$CC" >> isoverlapping_mex.mki
echo "CFLAGS=$CFLAGS" >> isoverlapping_mex.mki
echo "CLIBS=$CLIBS" >> isoverlapping_mex.mki
echo "COPTIMFLAGS=$COPTIMFLAGS" >> isoverlapping_mex.mki
echo "CDEBUGFLAGS=$CDEBUGFLAGS" >> isoverlapping_mex.mki
echo "CXX=$CXX" >> isoverlapping_mex.mki
echo "CXXFLAGS=$CXXFLAGS" >> isoverlapping_mex.mki
echo "CXXLIBS=$CXXLIBS" >> isoverlapping_mex.mki
echo "CXXOPTIMFLAGS=$CXXOPTIMFLAGS" >> isoverlapping_mex.mki
echo "CXXDEBUGFLAGS=$CXXDEBUGFLAGS" >> isoverlapping_mex.mki
echo "LD=$LD" >> isoverlapping_mex.mki
echo "LDFLAGS=$LDFLAGS" >> isoverlapping_mex.mki
echo "LDOPTIMFLAGS=$LDOPTIMFLAGS" >> isoverlapping_mex.mki
echo "LDDEBUGFLAGS=$LDDEBUGFLAGS" >> isoverlapping_mex.mki
echo "Arch=$Arch" >> isoverlapping_mex.mki
echo OMPFLAGS= >> isoverlapping_mex.mki
echo OMPLINKFLAGS= >> isoverlapping_mex.mki
echo "EMC_COMPILER=Clang" >> isoverlapping_mex.mki
echo "EMC_CONFIG=optim" >> isoverlapping_mex.mki
"/Users/venkat/Applications/Applications/MATLAB_R2014a.app/bin/maci64/gmake" -B -f isoverlapping_mex.mk
