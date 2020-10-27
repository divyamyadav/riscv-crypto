#!/bin/bash

set -x
set -e

SCALAR_OUT=adoc/riscv-crypto-scalar.adoc
VECTOR_OUT=adoc/riscv-crypto-vector.adoc
PANDOC="pandoc --from=latex --to=asciidoc"

rm -f $SCALAR_OUT

touch                                  $SCALAR_OUT
$PANDOC tex/sec-scalar-intro.tex        >> $SCALAR_OUT
$PANDOC tex/sec-scalar-bitmanip.tex     >> $SCALAR_OUT
$PANDOC tex/sec-scalar-aes.tex          >> $SCALAR_OUT
$PANDOC tex/sec-scalar-profiles.tex     >> $SCALAR_OUT
$PANDOC tex/sec-scalar-sha2.tex         >> $SCALAR_OUT
$PANDOC tex/sec-scalar-sm3.tex          >> $SCALAR_OUT
$PANDOC tex/sec-scalar-sm4.tex          >> $SCALAR_OUT
$PANDOC tex/sec-entropy-source.tex      >> $SCALAR_OUT
$PANDOC tex/sec-scalar.tex              >> $SCALAR_OUT
$PANDOC tex/appx-entropy.tex            >> $SCALAR_OUT

#appx-benchmarking.tex
#appx-materials.tex
#appx-scalar-encodings.tex
#appx-vector-encodings.tex
#changelog.tex
#sec-policies.tex
#sec-vector-aes.tex
#sec-vector-clmul.tex
#sec-vector-grev.tex
#sec-vector-intro.tex
#sec-vector-profiles.tex
#sec-vector-rotate.tex
#sec-vector-sha2.tex
#sec-vector.tex
