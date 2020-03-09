.name "Explosive Kitty"
	.comment "Jan-ken-pon (じゃんけんぽん)
	Ce qui reste éternellement incompréhensible dans la nature, c’est qu’on puisse la comprendre.
	Celui qui ne peut plus éprouver ni étonnement ni surprise, est pour ainsi dire mort : ses yeux sont éteints. – Albert Einstein
	Si vous voulez trouver les secrets de l'univers pensez en termes de fréquences, d'énergies et de vibrations. - Nikola Tesla
	Pas la pour etre ici. - Silicon Val[list]
	Dieu est la plus belle invention.
	Tapis dans l'ombre je veille. - Minou"

start:
		ld -42, r2
		zjmp %:begin
p2:
		ld %50986512, r10		# 02 90 03 09 fe 10 0a
		ld %-392, r9
		ld %84540929, r2		# 02 90 05 09 fe 01 02
		ld %-487, r3
		ld %118095856, r4		# 02 90 07 09 ff f0 04
		ld %-502, r5
		ld %-7, r7
		ld -511, r1
begin:
		ld %55575553, r8		# 02 90 03 50 04 01 08
		st r1, r15				# 03 50 01 0f
		st r8, -4				# 03 70 08 ff fc
		fork %:def
		live %42
		fork %:p2
def:
		ld %252645135, r4		# 02 90 0f 0f 0f 0f 04
		live %42
		ld 511, r1
		st r15, -27
