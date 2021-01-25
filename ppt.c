#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/**
 *                             Pythagorean Triples
 *
 * A pythagorean triplet (PT) consists of three natural numbers x, y and z
 * with x^2 + y^2 = z^2. PTs with greatest common divisor 1 (pPT) are of
 * particular interest.
 *
 * Theorem 1: Every PT can be obtained in a unique way as a product of a
 *            pPT and a natural number k.
 *
 * Theorem 2: In every pPT ( x | y | z ) one of the numbers x or y (legs)
 *            is even and the other one is odd. Let x always be the odd leg.
 *
 * Theorem 3: For every pPT ( x | y | z ) there exists one and only one pair
 *            ( m | n ) of relatively prime natural numbers of different
 *            parity, i.e. one of the numbers is even and the other is odd,
 *            with m < n, such that:
 *
 *                x = n^2 - m^2, y = 2mn , z = n^2 + m^2
 *
 *            resp.
 *
 *                1/2(z - x) = m^2, 1/2(z + x) = n^2.
 *
 * Theorem 4: Every pPT can in a unique way be obtained from ( 3 | 4 | 5 )
 *            by application of a sequence of transformations A, B or C.
 *            The transformations are defined by:
 *
 *            A: (x|y|z) --> ( x-2y+2z| 2x-y+2z| 2x-2y+3z)   [or (m|n) --> (n|2n-m)]
 *            B: (x|y|z) --> ( x+2y+2z| 2x+y+2z| 2x+2y+3z)   [or (m|n) --> (n|2n+m)]
 *            C: (x|y|z) --> (-x+2y+2z|-2x+y+2z|-2x+2y+3z)   [or (m|n) --> (m|2m+n)]
 *
 */

/**
 *                             Pythagoräische Tripel
 *
 * Ein pythagoräisches Tripel (PT) besteht aus drei natürlichen Zahlen x, y und z
 * mit x^2 + y^2 = z^2. Interessant sind teilerfremde PT, bei denen x, y und z den
 * größten gemeinsamen Teiler 1 besitzen (pPT).
 *
 * Satz 1: Jedes PT läßt sich auf genau eine Weise durch Multiplikation aus einem
 *         pPT und einer natürlichen Zahl gewinnen.
 *
 * Satz 2: In jedem pPT ( x | y | z ) ist eine der Zahlen x oder y (Katheten)
 *         gerade und die andere ungerade. Es sei x immer die ungerade Kathete.
 *
 * Satz 3: Zu jedem pPT ( x | y | z ) gibt es genau ein Paar ( m | n ) natürlicher
 *         teilerfremder Zahlen mit m < n und ungleicher Parität, d.h. eine der
 *         Zahlen ist gerade und die andere ungerade, so dass gilt:
 *
 *             x = n^2 - m^2, y = 2mn , z = n^2 + m^2
 *
 *         bzw.
 *
 *             1/2(z - x) = m^2, 1/2(z + x) = n2.
 *
 * Satz 4: Aus dem pPT ( 3 | 4 | 5 ) läßt sich jedes andere pPT auf genau eine
 *         Weise gewinnen durch eine Abfolge ("Sequenz") von Abbildungen A, B oder
 *         C, die hintereinander auf ( 3 | 4 | 5 ) angewendet werden.
 *         Die Abbildungsvorschriften sind definiert durch:
 *
 *         A: (x|y|z) --> ( x-2y+2z| 2x-y+2z| 2x-2y+3z)   [bzw. (m|n) --> (n|2n-m)]
 *         B: (x|y|z) --> ( x+2y+2z| 2x+y+2z| 2x+2y+3z)   [bzw. (m|n) --> (n|2n+m)]
 *         C: (x|y|z) --> (-x+2y+2z|-2x+y+2z|-2x+2y+3z)   [bzw. (m|n) --> (m|2m+n)]
 *
 */


#define	MAXPPT	1000000

#if !defined(SORT_BY)
#define SORT_BY 1
#endif
int maxppt;

/**
 * @brief Apply rule A to the triplet x, y, z
 * A: (x|y|z) --> ( x-2y+2z| 2x-y+2z| 2x-2y+3z)
 *
 */
static void ppt_A(int64_t* x, int64_t* y, int64_t* z)
{
	int64_t xn = *x - *y * 2 + *z * 2;
	int64_t yn = *x * 2 - *y + *z * 2;
	int64_t zn = *x * 2 - *y * 2 + *z * 3;
	*x = xn;
	*y = yn;
	*z = zn;
}

/**
 * @brief Apply rule B to the triplet x, y, z
 * B: (x|y|z) --> ( x+2y+2z| 2x+y+2z| 2x+2y+3z)
 *
 */
static void ppt_B(int64_t* x, int64_t* y, int64_t* z)
{
	int64_t xn = *x + *y * 2 + *z * 2;
	int64_t yn = *x * 2 + *y + *z * 2;
	int64_t zn = *x * 2 + *y * 2 + *z * 3;
	*x = xn;
	*y = yn;
	*z = zn;
}

/**
 * @brief Apply rule C to the triplet x, y, z
 * C: (x|y|z) --> (-x+2y+2z|-2x+y+2z|-2x+2y+3z)
 *
 */
static void ppt_C(int64_t* x, int64_t* y, int64_t* z)
{
	int64_t xn = - *x + *y * 2 + *z * 2;
	int64_t yn = - *x * 2 + *y + *z * 2;
	int64_t zn = - *x * 2 + *y * 2 + *z * 3;
	*x = xn;
	*y = yn;
	*z = zn;
}

typedef struct {
	int64_t x;	//!< the triple's x value (odd cathetus)
	int64_t y;	//!< the triple's y value (even cathetus)
	int64_t z;	//!< the triple's z value (hypotenuse)
	int32_t i;	//!< index of this triple's parent
	int32_t rule;	//!< rule applied to the parent triple
}	triple_t;

triple_t *ppt = NULL;

#if (SORT_BY == 1)
static int compare_triple(const void* p1, const void* p2)
{
	const triple_t* t1 = (const triple_t*)p1;
	const triple_t* t2 = (const triple_t*)p2;
	if (t1->x != t2->x)
		return t1->x < t2->x ? -1 : +1;
	if (t1->y != t2->y)
		return t1->y < t2->y ? -1 : +1;
	if (t1->z != t2->z)
		return t1->z < t2->z ? -1 : +1;
	return 0;
}
#endif

#if (SORT_BY == 2)
static int compare_triple(const void* p1, const void* p2)
{
	const triple_t* t1 = (const triple_t*)p1;
	const triple_t* t2 = (const triple_t*)p2;
	return t1->z < t2->z ? -1 : t1->z == t2->z ? 0 : +1;
}
#endif

void usage(const char* argv0)
{
	const char* progname = strrchr(argv0, '/') ? strrchr(argv0, '/') + 1 : argv0;
	printf("usage: %s [options] maxppt\n", progname);
	printf("where options is one of:\n");
	printf("-h     show thins help\n");
	printf("-p     show rule and parent PPT for each PPT\n");
	exit(1);
}

int main(int argc, char** argv)
{
	int show_parent = 0;
	int i, j, maxppt;

	maxppt = MAXPPT;
	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-p")) {
			show_parent = 1;
			continue;
		}
		if (!strcmp(argv[i], "-h")) {
			usage(argv[0]);
		}
		maxppt = strtoll(argv[i], NULL, 0);
		break;
	}

	triple_t* ppt = calloc(maxppt, sizeof(triple_t));
	if (!ppt) {
		perror("calloc()");
		return 1;
	}

	// Start off with the pPT 3,4,5 at index 0
	ppt[0].x = 3;
	ppt[0].y = 4;
	ppt[0].z = 5;
	ppt[0].i = 0;
	ppt[0].rule = 0;
	// apply rules A, B and C until we have maxppt pPTs
	for (i = 0, j = 1; j < maxppt; i++) {
		ppt[j] = ppt[i];
		ppt[j].i = i;
		ppt[j].rule = 1;
		ppt_A(&ppt[j].x, &ppt[j].y, &ppt[j].z);
		if (++j == maxppt)
			break;
		ppt[j] = ppt[i];
		ppt[j].i = i;
		ppt[j].rule = 2;
		ppt_B(&ppt[j].x, &ppt[j].y, &ppt[j].z);
		if (++j == maxppt)
			break;
		ppt[j] = ppt[i];
		ppt[j].i = i;
		ppt[j].rule = 3;
		ppt_C(&ppt[j].x, &ppt[j].y, &ppt[j].z);
		if (++j == maxppt)
			break;
	}
#if SORT_BY
	// Sort the triplets
	qsort(ppt, maxppt, sizeof(triple_t), compare_triple);
#endif

	for (i = 0; i < maxppt; i++) {
		j = ppt[i].i;
		if (show_parent) {
			printf("%10" PRId64 "^2 + %10" PRId64 "^2 = %10" PRId64 "^2" \
				" (%c %10" PRId64 "|%10" PRId64 "|%10" PRId64 ")\n",
				ppt[i].x, ppt[i].y, ppt[i].z,
				'@' + ppt[i].rule,
				ppt[j].x, ppt[j].y, ppt[j].z);
		} else {
			printf("%10" PRId64 "^2 + %10" PRId64 "^2 = %10" PRId64 "^2\n",
				ppt[i].x, ppt[i].y, ppt[i].z);
		}
	}
	free(ppt);
	return 0;
}
