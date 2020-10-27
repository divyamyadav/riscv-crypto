
ifndef REPO_HOME
    $(error "Please run 'source ./bin/conf.sh' to setup the project workspace")
endif

TEX = pdflatex 

BUILD_DIR = $(REPO_BUILD)/spec

OPCODES_SCALAR   = $(REPO_HOME)/doc/opcodes-crypto-scalar.adoc
OPCODES_VECTOR   = $(REPO_HOME)/doc/opcodes-crypto-vector.adoc

SPEC_SCALAR_IN   = $(REPO_HOME)/doc/adoc/riscv-crypto-scalar.adoc

SPEC_SCALAR_PDF  = riscv-crypto-spec-scalar.pdf
SPEC_VECTOR_PDF  = riscv-crypto-spec-vector.pdf

SPEC_SCALAR_HTML = riscv-crypto-spec-scalar.html
SPEC_VECTOR_HTML = riscv-crypto-spec-vector.html

SPEC_EXTRA= riscv-crypto-spec.sty $(OPCODES)
SPEC_COMMIT= $(BUILD_DIR)/spec.commit

.PHONY: $(SPEC_COMMIT)
$(SPEC_COMMIT):
	@mkdir -p $(BUILD_DIR)
	@git rev-parse --abbrev-ref HEAD > ${@}
	@echo "@" >> ${@}
	@git log --pretty=format:'%H' -n 1 >> ${@}

$(OPCODES_SCALAR) : $(REPO_HOME)/tools/opcodes-crypto-scalar
	@mkdir -p $(dir $(OPCODES_SCALAR))
	cat $^ | python3 $(REPO_HOME)/bin/parse_opcodes.py -tex > $@

$(OPCODES_VECTOR) : $(REPO_HOME)/tools/opcodes-crypto-vector
	@mkdir -p $(dir $(OPCODES_VECTOR))
	cat $^ | python3 $(REPO_HOME)/bin/parse_opcodes.py -tex > $@

$(SPEC_SCALAR_PDF) : $(SPEC_SCALAR_IN)
	asciidoctor-pdf -n -d book -b pdf -o $@ $<

$(SPEC_SCALAR_HTML) : $(SPEC_SCALAR_IN)
	asciidoctor -n -b html -o $@ $<

spec-scalar: $(SPEC_SCALAR_PDF) $(SPEC_SCALAR_HTML)
spec-vector: $(SPEC_VECTOR_PDF) $(SPEC_VECTOR_HTML)

specs: spec-scalar spec-vector

clean:
	rm -rf $(BUILD_DIR)/* $(OPCODES) \
		*.aux *.bbl *.blg *.log *.out *.pdf *.run.xml *-blx.bib *.toc
