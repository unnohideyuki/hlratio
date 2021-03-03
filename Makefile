hlratio_test: hlratio_test.cc hlratio.cc hlratio.h
	g++ -O2 -Wall --std=gnu++17 $< -lgtest -lgtest_main -lpthread -o $@

check:	hlratio_test
	./$<
