#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>

int sstrcmp(const char* s1, const char* s2) {
	while (*s1 && (*s1 == *s2)) {
		s1++;
		s2++;
	}
	return *(unsigned char*)s1 - *(unsigned char*)s2;
}

size_t sstrlen(const char* str) {
	const char* start = str;

	while (*str) {
		str++;
	}

	return str - start;
}

char* sstrcpy(char* dest, const char* src) {
	char* p = dest;
	while ((*p++ = *src++));
	return dest;
}

size_t* handle_l(const char* str) {

	if (str == NULL) {
		return -1;
	}

	size_t length = sstrlen(str);
	size_t *result = (size_t*)malloc(sizeof(size_t));

	if (result == NULL) {
		return -2;
	}

	*result = length;
	return result;
}

char* handle_r(const char* str) {

	if (str == NULL) {
		return -1;
	}

	size_t length = sstrlen(str);
	char* result = (char*)malloc(length + 1);

	if (result == NULL) {
		return -2;
	}

	const char* end = str + length - 1;
	char* dest = result;

	while (end >= str) {
		*dest++ = *end--;
	}

	*dest = '\0';

	return result;
}

char* handle_u(const char* str) {
	if (str == NULL) {
		return -1;
	}

	size_t length = sstrlen(str);
	size_t i;
	char* result = (char*)malloc(length + 1);

	if (result == NULL) {
		return -2;
	}

	for (i = 0; i < length; i++) {
		if (i % 2 == 0) {
			if (str[i] >= 'a' && str[i] <= 'z') {
				result[i] = str[i] - 32;
			}
			else {
				result[i] = str[i];
			}
		}
		else {
			result[i] = str[i];
		}
	}
	result[length] = '\0';
	return result;
}

char* handle_n(const char* str) {
	if (str == NULL)
	{
		return -1;
	}

	size_t length = sstrlen(str);
	char* result = (char*)malloc(length + 1);
	if (result == NULL)
	{
		return -2;
	}

	size_t pos_d = 0;

	for (size_t i = 0; i < length; i++) {
		if (str[i] >= '0' && str[i] <= '9')
		{
			result[pos_d++] = str[i];
		}
	}

	size_t pos_l = 0;
	size_t start_l = pos_d;

	for (size_t i = 0; i < length; i++) {
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		{
			result[start_l + pos_l++] = str[i];
		}
	}

	size_t pos_o = 0;
	size_t start_o = start_l + pos_l;

	for (size_t i = 0; i < length; i++) {
		if (!((str[i] >= '0' && str[i] <= '9') ||
			(str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z'))) {
			result[start_o + pos_o++] = str[i];
		}
	}

	result[length] = '\0';
	return result;
}

char* handle_c(int argc, char* argv[]) {
	if (argc < 5)
	{
		return 1;
	}
	
	int i;
	int seed = argv[2];
	srand((unsigned int)seed);

	int count = 0;

	if (argc > 2)
	{
		count++;
	}

	for (int i = 5; i < argc; i++) {
		count++;
	}

	if (count == 0) {
		return 2;
	}

	char** selected = (char**)malloc(count * sizeof(char*));
	if (selected == NULL)
	{
		return -2;
	}

	int idx = 0;
	if (argc > 2)
	{
		selected[idx++] = argv[2];
	}

	for (int i = 5; i < argc; i++) {
		selected[idx++] = argv[i];
	}

	for (i = count - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		char* temp = selected[i];
		selected[i] = selected[j];
		selected[j] = temp;
	}

	size_t total_len = 0;
	for (i = 0; i < count; i++) {
		total_len += sstrlen(selected[i]);
	}

	char* result = (char*)malloc(total_len + 1);
	if (result == NULL)
	{
		free(selected);
		return -2;
	}

	char* ptr = result;
	for (i = 0; i < count; i++) {
		const char* src = selected[i];
		while (*src) {
			*ptr++ = *src++;
		}
	}
	*ptr = '\0';

	free(selected);
	return result;
}

int main(int argc, char *argv[]) {

	if (argc < 3) {
		printf("\n[ERROR] - Usage example: %s <flag> <string> <args...>\n", argv[0]);
		return 1;
	}

	const char* flag = argv[1];
	const char* must_str = argv[2];

	if (sstrcmp(flag, "-l") == 0) {

		size_t *result = handle_l(must_str); 

		printf("\nLength of string \"%s\" - %zu.\n", must_str, *result);

		free(result);
		return 0;
		}

		else if (sstrcmp(flag, "-r") == 0)
	{

		char* result = handle_r(must_str);

		printf("\nReversed string: \"%s\"\n", result);
		free(result);
		return 0;
	}

		else if (sstrcmp(flag, "-u") == 0)
	{

		char* result = handle_u(must_str);

		printf("\nNew string: \"%s\"\n", result);
		free(result);
		return 0;
	}

		else if (sstrcmp(flag, "-n") == 0) {
		
		char* result = handle_n(must_str);

		printf("\nNew string: \"%s\"\n", result);
		free(result);
		return 0;
	}
		else if (sstrcmp(flag, "-c") == 0)
	{
		char* result = handle_c(argc, argv);\

			if (result == 1)
			{
				printf("\n[ERROR] - Not enough arguments for -c\n");
		    }
			else
			{
				printf("\nNew string: \"%s\"\n", result);
				free(result);
			}
	}

		else {
			printf("\n[ERROR] - Unknown flag: %s\n", flag);
		}

	return 0;
}