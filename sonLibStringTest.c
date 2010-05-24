/*
 * sonLibStringTest.c
 *
 *  Created on: 24-May-2010
 *      Author: benedictpaten
 */

#include "sonLibGlobalsPrivate.h"

void testString_copy(CuTest* testCase) {
	const char *test[3] = { "hello this is a test", "", "BOO\nTOO\n" };
	int32_t i;
	for(i=0; i<3; i++) {
		char *testCopy = string_copy(test[i]);
		CuAssertTrue(testCase, testCopy != test[i]);
		CuAssertStrEquals(testCase, test[i], testCopy);
		free(testCopy);
	}
}

void testString_print(CuTest* testCase) {
	char *cA = string_print("Hello %s, foo %i %.1f", "world", 5, 7.0);
	CuAssertStrEquals(testCase, "Hello world, foo 5 7.0", cA);
	free(cA);
	cA = string_print("");
	CuAssertStrEquals(testCase, "", cA);
	free(cA);
}

void testString_getNextWord(CuTest* testCase) {
	const char *cA = "Hello    world \n 5 \t6.0 ( )";
	char **pointer = (char **)&cA;
	char *cA2;
	cA2 = string_getNextWord(pointer);
	CuAssertStrEquals(testCase, "Hello", cA2);
	free(cA2);
	cA2 = string_getNextWord(pointer);
	CuAssertStrEquals(testCase, "world", cA2);
	free(cA2);
	cA2 = string_getNextWord(pointer);
	CuAssertStrEquals(testCase, "5", cA2);
	free(cA2);
	cA2 = string_getNextWord(pointer);
	CuAssertStrEquals(testCase, "6.0", cA2);
	free(cA2);
	cA2 = string_getNextWord(pointer);
	CuAssertStrEquals(testCase, "(", cA2);
	free(cA2);
	cA2 = string_getNextWord(pointer);
	CuAssertStrEquals(testCase, ")", cA2);
	free(cA2);
	CuAssertTrue(testCase, string_getNextWord(pointer) == NULL);
	CuAssertTrue(testCase, string_getNextWord(pointer) == NULL);
}

void testString_replace(CuTest* testCase) {
	char *cA = string_replace("Hello world wowo", "wo", " foo ");
	CuAssertStrEquals(testCase, "Hello  foo rld  foo  foo ", cA);
	free(cA);
}

void testString_join(CuTest* testCase) {
	const char *cA[3] = { "Hello world wo", "wo", " foo " };
	char *cA2 = string_join("\n", cA, 3);
	CuAssertStrEquals(testCase, "Hello world wo\nwo\n foo ", cA2);
	free(cA2);
}

CuSuite* stringTestSuite(void) {
	CuSuite* suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, testString_copy);
	SUITE_ADD_TEST(suite, testString_print);
	SUITE_ADD_TEST(suite, testString_getNextWord);
	SUITE_ADD_TEST(suite, testString_replace);
	SUITE_ADD_TEST(suite, testString_join);
	return suite;
}


