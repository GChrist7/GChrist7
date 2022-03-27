from Bio import SeqIO


print("MN908947.3 corresponde ao organismo 'Severe acute respiratory syndrome coronavirus 2 isolate Wuhan-Hu-1'.")
print("MT012098 corresponde ao organismo 'Severe acute respiratory syndrome coronavirus 2 isolate SARS-CoV-2/human/IND/29/2020'")
print("MZ264787.1 corresponde ao organismo 'Severe acute respiratory syndrome coronavirus 2 isolate SARS-CoV-2/human/BRA/CD1739-P4/2020'")
print("NC_019843.3 corresponde ao organismo 'Middle East respiratory syndrome-related coronavirus isolate HCoV-EMC/2012'")
print()

#Letra b) Cálculo do tamanho das sequências
print("Tamanho das sequências: ")
for seq1 in SeqIO.parse("seq1.fasta", "fasta"):
    print("Tamanho da sequência 1 (seq1):", len(seq1))
for seq2 in SeqIO.parse("seq2.fasta", "fasta"):
    print("Tamanho da sequência 2 (seq2):", len(seq2))
for seq3 in SeqIO.parse("seq3.fasta", "fasta"):
    print("Tamanho da sequência 3 (seq3):", len(seq3))
for seq4 in SeqIO.parse("seq4.fasta", "fasta"):
    print("Tamanho da sequência 4 (seq4):", len(seq4))



#Letra c) Criação dos gráficos da frequência de nucleotídeos nos genomas

from collections import Counter
import matplotlib.pyplot as plt

s1 = sorted(seq1)
s2 = sorted(seq2)
s3 = sorted(seq3)
s4 = sorted(seq4)

freq1 = Counter(s1)
freq2 = Counter(s2)
freq3 = Counter(s3)
freq4 = Counter(s4)
plt.subplot(2,2,1)
plt.title("Frequência Genoma MN908947.3")
plt.bar(freq1.keys(), freq1.values())
plt.subplot(2,2,2)
plt.title("Frequência Genoma MT012098")
plt.bar(freq2.keys(), freq2.values())
plt.subplot(2,2,3)
plt.title("Frequência Genoma MZ264787.1")
plt.bar(freq3.keys(), freq3.values())
plt.subplot(2,2,4)
plt.title("Frequência Genoma NC_019843.3")
plt.bar(freq4.keys(), freq4.values())

plt.show()


#Letra d)

#Cálculo das %GC de cada Genoma
from Bio.SeqUtils import GC
print()
print('Cálculo das %GC de cada Genoma:')
print("%GC da seq1:", '%0.2f' % GC(seq1.seq))
print("%GC da seq2:", '%0.2f' % GC(seq2.seq))
print("%GC da seq3:", '%0.2f' % GC(seq3.seq))
print("%GC da seq4:", '%0.2f' % GC(seq4.seq))
print()

#Cálculo das temperaturas de melting de cada Genoma.
print('Cálculo das temperaturas de melting de cada Genoma:')
tm1 = 64.9 +0.41*(GC(seq1.seq)) - (500/len(seq1))
tm2 = 64.9 +0.41*(GC(seq2.seq)) - (500/len(seq2))
tm3 = 64.9 +0.41*(GC(seq3.seq)) - (500/len(seq3))
tm4 = 64.9 +0.41*(GC(seq4.seq)) - (500/len(seq4))
print("Temperatura de melting da seq1:", '%0.2f' % tm1, "ºC")
print("Temperatura de melting da seq1:", '%0.2f' % tm2, "ºC")
print("Temperatura de melting da seq1:", '%0.2f' % tm3, "ºC")
print("Temperatura de melting da seq1:", '%0.2f' % tm4, "ºC")

#Letra e) Alinhamento global 2 a 2 dos 800 primeiros nucleotídeos de todas as sequências

from Bio import pairwise2 as p2
print()
print('Alinhamentos:')
for seq1_vs_seq2 in p2.align.globalxx(seq1.seq[0:800],seq2.seq[0:800],one_alignment_only=True):
    print("Alinhamento da seq1 com a seq2: ")
    print(p2.format_alignment(*seq1_vs_seq2))
    print("Similaridade: ", '%0.2f' % ((p2.align.globalxx(seq1.seq[0:800], seq2.seq[0:800], one_alignment_only=True, score_only=True) / 800) * 100), "%")
    print()
for seq1_vs_seq3 in p2.align.globalxx(seq1.seq[0:800],seq3.seq[0:800],one_alignment_only=True):
    print("Alinhamento da seq1 com a seq3: ")
    print(p2.format_alignment(*seq1_vs_seq3))
    print("Similaridade: ", '%0.2f' % ((p2.align.globalxx(seq1.seq[0:800], seq3.seq[0:800], one_alignment_only=True, score_only=True) / 800) * 100), "%")
    print()
for seq1_vs_seq4 in p2.align.globalxx(seq1.seq[0:800], seq4.seq[0:800], one_alignment_only=True):
    print("Alinhamento da seq1 com a seq4: ")
    print(p2.format_alignment(*seq1_vs_seq4))
    print("Similaridade: ", '%0.2f' % ((p2.align.globalxx(seq1.seq[0:800], seq4.seq[0:800], one_alignment_only=True, score_only=True) / 800) * 100), "%")
    print()
for seq2_vs_seq3 in p2.align.globalxx(seq2.seq[0:800],seq3.seq[0:800],one_alignment_only=True):
    print("Alinhamento da seq2 com a seq3: ")
    print(p2.format_alignment(*seq2_vs_seq3))
    print("Similaridade: ", '%0.2f' % ((p2.align.globalxx(seq2.seq[0:800], seq3.seq[0:800], one_alignment_only=True, score_only=True) / 800) * 100), "%")
    print()
for seq2_vs_seq4 in p2.align.globalxx(seq2.seq[0:800],seq4.seq[0:800],one_alignment_only=True):
    print("Alinhamento da seq2 com a seq4: ")
    print(p2.format_alignment(*seq2_vs_seq4))
    print("Similaridade: ", '%0.2f' % ((p2.align.globalxx(seq2.seq[0:800], seq4.seq[0:800], one_alignment_only=True, score_only=True) / 800) * 100), "%")
    print()
for seq3_vs_seq4 in p2.align.globalxx(seq3.seq[0:800],seq4.seq[0:800],one_alignment_only=True):
    print("Alinhamento da seq3 com a seq4: ")
    print(p2.format_alignment(*seq3_vs_seq4))
    print("Similaridade: ", '%0.2f' % ((p2.align.globalxx(seq3.seq[0:800], seq4.seq[0:800], one_alignment_only=True, score_only=True) / 800) * 100), "%")
    print()

#Letra f) Síntese protéica das sequências e criação do gráfico de frequências de aminoácidos

import warnings
from Bio import BiopythonWarning
warnings.simplefilter('ignore', BiopythonWarning)

print()
print('Tradução das proteínas:')
prot1 = seq1.seq[0:].translate()
print("Tradução da seq1: ")
print(prot1)
print(200 * '-')
prot2 = seq2.seq[0:].translate()
print("Tradução da seq2: ")
print(prot2)
print(200 * '-')
prot3 = seq3.seq[0:].translate()
print("Tradução da seq3: ")
print(prot3)
print(200 * '-')
prot4 = seq4.seq[0:].translate()
print("Tradução da seq4: ")
print(prot4)
print(200 * '-')

fprot1 = sorted(prot1)
fprot1 = Counter(fprot1)
fprot2 = sorted(prot2)
fprot2 = Counter(fprot2)
fprot3 = sorted(prot3)
fprot3 = Counter(fprot3)
fprot4 = sorted(prot4)
fprot4 = Counter(fprot4)


plt.subplot(2,2,1)
plt.title("Frequências dos aminoácidos na proteína traduzida da seq1:")
plt.bar(fprot1.keys(), fprot1.values())
plt.subplot(2,2,2)
plt.title("Frequências dos aminoácidos na proteína traduzida da seq2:")
plt.bar(fprot2.keys(), fprot2.values())
plt.subplot(2,2,3)
plt.title("Frequências dos aminoácidos na proteína traduzida da seq3:")
plt.bar(fprot3.keys(), fprot3.values())
plt.subplot(2,2,4)
plt.title("Frequências dos aminoácidos na proteína traduzida da seq4:")
plt.bar(fprot4.keys(), fprot4.values())

plt.show()


#letra g) Determinação das estruturas secundárias das proteínas traduzidas.

from Bio.SeqUtils.ProtParam import ProteinAnalysis
print()
print('Análise das proteínas:')

print('Estruturas secundárias da proteína traduzida da seq1: ')
prot1Analysis = ProteinAnalysis(str(prot1))
print("% de alpha-hélices: ",  '%0.2f' % (prot1Analysis.secondary_structure_fraction()[0]*100))
print("% de Dobras-Beta: ", '%0.2f' % (prot1Analysis.secondary_structure_fraction()[1]*100))
print("% de Lâminas-Beta: ", '%0.2f' % (prot1Analysis.secondary_structure_fraction()[2]*100))
print()

print('Estruturas secundárias da proteína traduzida da seq2: ')
prot2Analysis = ProteinAnalysis(str(prot2))
print("% de alpha-hélices: ", '%0.2f' % (prot2Analysis.secondary_structure_fraction()[0]*100))
print("% de Dobras-Beta: ", '%0.2f' % (prot2Analysis.secondary_structure_fraction()[1]*100))
print("% de Lâminas-Beta: ", '%0.2f' % (prot2Analysis.secondary_structure_fraction()[2]*100))
print()

print('Estruturas secundárias da proteína traduzida da seq3: ')
prot3Analysis = ProteinAnalysis(str(prot3))
print("% de alpha-hélices: ", '%0.2f' % (prot3Analysis.secondary_structure_fraction()[0]*100))
print("% de Dobras-Beta: ", '%0.2f' % (prot3Analysis.secondary_structure_fraction()[1]*100))
print("% de Lâminas-Beta: ", '%0.2f' % (prot3Analysis.secondary_structure_fraction()[2]*100))
print()

print('Estruturas secundárias da proteína traduzida da seq4: ')
prot4Analysis = ProteinAnalysis(str(prot4))
print("% de alpha-hélices: ", '%0.2f' % (prot4Analysis.secondary_structure_fraction()[0]*100))
print("% de Dobras-Beta: ", '%0.2f' % (prot4Analysis.secondary_structure_fraction()[1]*100))
print("% de Lâminas-Beta: ", '%0.2f' % (prot4Analysis.secondary_structure_fraction()[2]*100))















