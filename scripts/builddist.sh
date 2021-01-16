# build file to generate the distribution binary tarball

make clean

./configure \
  $PKGCFG \
  $CROSSCFG \
  --with-ptw32=$PREFIX/i686-w64-mingw32.static \
  --enable-static \
  PTW32_LIBS="-lpthread -lpcreposix -lpcre" \
  FLTK_CONFIG=$PREFIX/bin/i686-w64-mingw32.static-fltk-config \

make

$PREFIX/bin/i686-pc-mingw32-strip src/comptext.exe
make nsisinst
mv src/*setup*exe .

make clean

# build the distribution tarball
./configure
make distcheck
make clean
