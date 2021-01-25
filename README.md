# Thoughts about the perfect cuboid.

The unsolved problem of whether a perfect cuboid exists or not,
or whether there is a proof pro or contra its existence...
See for example http://unsolvedproblems.org/index_files/PerfectCuboid.htm

I believe to have a simple proof using logic and *Reductio ad absurdum*
for the assumption that there is a smallest solution.

The 10th (or so) try to explain my reasoning is here:

+ English [cuboid-x.pdf](cuboid-x.pdf).
+ German [cuboid-x.de.pdf](cuboid-x.de.pdf).
+ Polish [cuboid-x.pl.pdf](cuboid-x.pl.pdf).

# Print a list of Primitive Pythagorean Triples

This little program creates perfect Pythogarean triples by applying
a sequence of one out of three build rules starting with the first
pPT x = 3, y = 4 and z = 5.

                            Pythagorean Triples

A pythagorean triplet (PT) consists of three natural numbers x, y and z
with x^2 + y^2 = z^2. PTs with greatest common divisor 1 (pPT) are of
particular interest.

Theorem 1: Every PT can be obtained in a unique way as a product of a
           pPT and a natural number k.

Theorem 2: In every pPT ( x | y | z ) one of the numbers x or y (legs)
           is even and the other one is odd. Let x always be the odd leg.

Theorem 3: For every pPT ( x | y | z ) there exists one and only one pair
           ( m | n ) of relatively prime natural numbers of different
           parity, i.e. one of the numbers is even and the other is odd,
           with m < n, such that:

               x = n^2 - m^2, y = 2mn , z = n^2 + m^2

           resp.

               1/2(z - x) = m^2, 1/2(z + x) = n^2.

Theorem 4: Every pPT can in a unique way be obtained from ( 3 | 4 | 5 )
           by application of a sequence of transformations A, B or C
           defined by:

           A: (x|y|z) --> ( x-2y+2z| 2x-y+2z| 2x-2y+3z)   [or (m|n) --> (n|2n-m)]
           B: (x|y|z) --> ( x+2y+2z| 2x+y+2z| 2x+2y+3z)   [or (m|n) --> (n|2n+m)]
           C: (x|y|z) --> (-x+2y+2z|-2x+y+2z|-2x+2y+3z)   [or (m|n) --> (m|2m+n)]
