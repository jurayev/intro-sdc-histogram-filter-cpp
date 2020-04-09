#include <localizer.h>
#include <gtest/gtest.h>
#include <helpers.h>

using namespace std;

TEST(HistogramFilterTests, Normalize) {
	// Arrange
	vector < vector <float> > unnormalized, normalized, result;
	unnormalized = zeros(2, 2);
	normalized = zeros(2, 2);

	for (int i=0; i<2; i++) {
		for(int j=0; j<2; j++) {
			unnormalized[i][j] = 1.0;
			normalized[i][j] = 0.25;
		}
	}
	// Act
	result = normalize(unnormalized);
	// Assert
	ASSERT_EQ(normalized, result) << "beliefs were not normalized";
}

TEST(HistogramFilterTests, Blur) {
	vector < vector <float> > in, correct, out;
	in = zeros(3, 3);
	correct = zeros(3,3);

	in[1][1] = 1.0;

	float corner = 0.01;
	float side = 0.02;
	float center = 0.88;

	correct = {
			{corner, side, corner},
			{side, center, side},
			{corner, side, corner}
	};

	out = blur(in, 0.12);

	bool is_close = close_enough(out, correct);
	ASSERT_TRUE(is_close);
}

TEST(HistogramFilterTests, InitializeBeliefs){
	vector < vector <char> > map;
	map = read_map("../../maps/m1.txt");
	vector < vector <float> > beliefs, correct;

	int r, c, A;
	float belief;

	r = map.size();
	c = map[0].size();
	A = r * c;
	belief = 1.0 / A;

	int i, j;
	vector <float> row;
	for (i=0; i<r; i++) {
		row.clear();
		for (j=0; j<c; j++) {
			row.push_back(belief);
		}
		correct.push_back(row);
	}

	beliefs = initialize_beliefs(map);

	ASSERT_EQ(beliefs, correct);

}

TEST(HistogramFilterTests, Move) {
	vector < vector <float> > in, out, correct;
	in = zeros(3,3);
	in[2][2] = 1.0;

	int dx, dy;
	dx = 1;
	dy = 1;
	float blurring = 0.0;

	correct = zeros(3,3);
	correct[0][0] = 1.0;

	out = move(dy, dx, in, blurring);

	ASSERT_EQ(out, correct);
}

TEST(HistogramFilterTests, Sense) {
	vector < vector <float> > in, out, correct;
	in = zeros(4,2);
	in[2][1] = 1.0;

	int i,j;
	for (i=0; i<in.size(); i++)
	{
		for (j=0; j<in[0].size(); j++) {
			in[i][j] = 1.0/8.0;
		}
	}

	char color = 'r';
	vector < vector <char> > map;
	map = read_map("../../maps/half_red.txt");
	float p_hit, p_miss;
	p_hit = 2.0;
	p_miss = 1.0;

	out = sense(color, map, in, p_hit, p_miss);
	float total = 0.0;

	for (i=0; i<out.size(); i++)
	{
		for (j=0; j<out[0].size(); j++) {
			total += out[i][j];
		}
	}

	EXPECT_GE(total, 0.99);
	EXPECT_LE(total, 1.01);

	EXPECT_EQ(out.size(), in.size());
	EXPECT_EQ(out[0].size(), in[0].size());

	float r_prob, g_prob, r_exp, g_exp;
	r_prob = out[0][0];
	g_prob = out[0][1];

	r_exp = 1.0 / 6.0;
	g_exp = 1.0 / 12.0;

	EXPECT_EQ(r_prob, r_exp);
	EXPECT_EQ(g_prob, g_exp);
}
