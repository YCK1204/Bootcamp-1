#include "MyLib.h"

char* Trim(char* str) {
	if (str == NULL)
		return NULL;

	int start = 0;
	int end = strlen(str) - 1;
	while (str[start] && isspace(str[start]))
		start++;
	while (end > start && isspace(str[end]))
		end--;
	return Substr(str, start, end - start + 1);
}

char* _Substr(char* str, int start) {
	if (str == NULL || start < 0)
		return NULL;

	int len = strlen(str);
	char* ret = (char*)malloc(sizeof(char) * (len + 1));
	for (int i = 0; i < str[i]; i++)
		ret[i] = str[i];
	ret[len] = 0;
	return ret;
}

char* Substr(char* str, int start, int count) {
	if (str == NULL || start < 0 || count < 0)
		return NULL;
	int len = strlen(str);

	if (len < start || len - start < count)
		return NULL;
	char* ret = (char*)malloc(sizeof(char) * (count + 1));
	for (int i = 0; i < count; i++) {
		ret[i] = str[i + start];
	}
	ret[count] = 0;
	return ret;
}

char* Getline(int fd) {
	static char* remainWords = NULL;
	char buf[BUFFER_SIZE + 1];

	while (true) {
		int n = _read(fd, buf, BUFFER_SIZE);
		if (n <= 0) {
			fprintf(stderr, "Error: Invalid fd access");
			return NULL;
		}
		buf[n] = 0;
		size_t size = 0;
		if (remainWords == NULL) {
			remainWords = _strdup(buf);
		}
		else {
			size = _msize(remainWords);
			remainWords = (char*)realloc(remainWords, sizeof(char) * (size + n));
			char* tmp = StrJoin(remainWords, buf);
			free(remainWords);
			remainWords = _strdup(tmp);
			free(tmp);
			size--;
		}

		for (size_t i = size; remainWords[i]; i++) {
			if (remainWords[i] == '\n') {
				remainWords[i] = 0;
				char* ret = _Substr(remainWords, 0);
				if (remainWords[i + 1] == 0) {
					free(remainWords);
					remainWords = NULL;
				}
				else {
					char* tmp = _Substr(remainWords, i + 1);
					free(remainWords);
					remainWords = _strdup(tmp);
					free(tmp);
				}
				return ret;
			}
		}
	}
	return NULL;
}

char** Split(char* str, int delim, bool trim) {
	if (str == NULL || delim == 0)
		return NULL;

	int cnt = 0;
	int i = 0;
	while (str[i]) {
		while (str[i] && str[i] == delim)
			i++;
		if (str[i] && str[i] != delim) {
			cnt++;
			while (str[i] && str[i] != delim)
				i++;
		}
	}

	char** ret = (char**)malloc(sizeof(char*) * (cnt + 1));
	i = 0;
	int j = 0;
	while (str[j]) {
		while (str[j] && str[j] == delim)
			j++;
		int start = j;
		while (str[j] && str[j] != delim)
			j++;
		char *tmp = Substr(str, start, j - start);
		if (trim) {
			ret[i] = Trim(tmp);
			free(tmp);
		}
		else {
			ret[i] = Trim(tmp);
		}
		i++;
	}
	ret[cnt] = NULL;
	return ret;
}

char* StrJoin(char* s1, char* s2) {
	if (s1 == NULL || s2 == NULL)
		return NULL;

	int len1 = strlen(s1);
	int len2 = strlen(s2);
	char* ret = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
	for (int i = 0; s1[i]; i++) { ret[i] = s1[i]; }
	for (int i = 0; s2[i]; i++) { ret[i + len1] = s2[i]; }
	ret[len1 + len2] = 0;
	return ret;
}