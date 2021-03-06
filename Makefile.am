
if WANT_JANSSON
JANSSON_INCLUDES= -I$(top_srcdir)/compat/jansson
else
JANSSON_INCLUDES=
endif

EXTRA_DIST	= example-cfg.json nomacro.pl

SUBDIRS		= compat

INCLUDES	= $(PTHREAD_FLAGS) -fno-strict-aliasing $(JANSSON_INCLUDES)

bin_PROGRAMS	= minerd

dist_man_MANS	= minerd.1

minerd_SOURCES	= elist.h \
		  miner.h \
		  compat.h \
		  algorithm.h \
		  cpu-miner.c \
		  util.c \
		  algorithm.c \
		  algorithm/sha2.c \
		  algorithm/scrypt.c \
		  algorithm/scrypt-jane.c \
		  algorithm/argon2a.c \
		  algorithm/dcrypt.c \
		  algorithm/dcrypt_sha256.c \
		  algorithm/yescrypt.c \
		  algorithm/keccak.c \
		  algorithm/twe.c \
		  algorithm/heavy.c \
		  algorithm/quark.c \
		  algorithm/qubit.c \
		  algorithm/skein.c \
		  algorithm/skein2.c \
		  algorithm/s3.c \
		  algorithm/ink.c \
		  algorithm/groestl.c \
		  algorithm/myriadcoin-groestl.c \
		  algorithm/decred.c \
		  algorithm/blake.c \
		  algorithm/blakecoin.c \
		  algorithm/cryptonight.c \
		  algorithm/fresh.c \
		  algorithm/hmq1725.c \
		  algorithm/lbry.c \
		  algorithm/nist5.c \
		  algorithm/sib.c \
		  algorithm/veltor.c \
		  algorithm/x11.c \
		  algorithm/x13.c \
		  algorithm/x14.c \
		  algorithm/x15.c \
		  algorithm/pentablake.c \
		  algorithm/axiom.c \
		  algorithm/timetravel.c \
		  algorithm/Lyra2RE.c \
		  algorithm/Lyra2RErev2.c \
		  algorithm/xzc.c \
		  algorithm/pluck.c \
		  algorithm/whirlcoin.c \
		  algorithm/whirlpoolx.c \
		  algorithm/xevan.c \
		  lyra2/Lyra2.c \
		  lyra2/Sponge.c \
		  ar2/src/cores.c \
		  ar2/src/blake2/blake2b.c \
		  ar2/src/opt.c \
		  ar2/src/argon2.c \
		  sha3/sph_keccak.c \
		  sha3/sph_hefty1.c \
		  sha3/sph_groestl.c \
		  sha3/sph_gost.c \
		  sha3/sph_skein.c \
		  sha3/sph_bmw.c \
		  sha3/sph_jh.c \
		  sha3/sph_sha0.c \
		  sha3/sph_sha1.c \
		  sha3/sph_sha2.c \
		  sha3/sph_sha2big.c \
		  sha3/sph_shavite.c \
		  sha3/sph_blake.c \
		  sha3/sph_luffa.c \
		  sha3/sph_cubehash.c \
		  sha3/sph_simd.c \
		  sha3/sph_echo.c \
		  sha3/sph_hamsi.c \
		  sha3/sph_haval.c \
		  sha3/sph_md2.c \
		  sha3/sph_md4.c \
		  sha3/sph_md5.c \
		  sha3/sph_panama.c \
		  sha3/sph_radiogatun.c \
		  sha3/sph_ripemd.c \
		  sha3/sph_tiger.c \
		  sha3/sph_fugue.c \
		  sha3/sph_shabal.c \
		  sha3/sph_whirlpool.c \
		  yescrypt/sha256_Y.c \
		  yescrypt/yescrypt-best.c \
		  yescrypt/yescryptcommon.c \
		  crypto/oaes_lib.c \
		  crypto/c_keccak.c \
		  crypto/c_groestl.c \
		  crypto/c_blake256.c \
		  crypto/c_jh.c \
		  crypto/c_skein.c \
		  crypto/mshabal.c \
		  crypto/hash.c \
		  crypto/aesb.c
if USE_ASM
if ARCH_x86
minerd_SOURCES += algorithm/sha2-x86.S algorithm/scrypt-x86.S algorithm/aesb-x86.S crypto/aesb-x86-impl.c
endif
if ARCH_x86_64
minerd_SOURCES += algorithm/sha2-x64.S algorithm/scrypt-x64.S algorithm/aesb-x64.S
endif
if ARCH_ARM
minerd_SOURCES += algorithm/sha2-arm.S algorithm/scrypt-arm.S
endif
endif

minerd_LDFLAGS	= $(PTHREAD_FLAGS)
minerd_LDADD	= @LIBCURL_LIBS@ @OPENSSL_LIBS@ @JANSSON_LIBS@ @PTHREAD_LIBS@ @WS2_LIBS@
minerd_CPPFLAGS = @LIBCURL_CPPFLAGS@ @LIBCURL_CFLAGS@
minerd_CFLAGS   = 

if HAVE_WINDOWS
minerd_CFLAGS += -Wl,--stack,10485760
minerd_LDFLAGS += -all-static
endif
