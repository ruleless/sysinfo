#include "utils.h"
#include "common/common.h"

const char * formatInteger(sigar_uint64_t n)
{
	static char s_formatStr[MAX_BUF];

	char exstr[MAX_BUF] = {0};
	s_formatStr[0] = '\0';
	while (n > 0)
	{
		int k = n % 1000;

		if (strlen(exstr) > 0)
		{
			if (n >= 1000)
			{
				__snprintf(s_formatStr, sizeof(s_formatStr), "%03d,%s", k, exstr);
			}
			else
			{
				__snprintf(s_formatStr, sizeof(s_formatStr), "%d,%s", k, exstr);
			}
		}
		else
		{
			if (n >= 1000)
			{
				__snprintf(s_formatStr, sizeof(s_formatStr), "%03d", k);
			}
			else
			{
				__snprintf(s_formatStr, sizeof(s_formatStr), "%d", k);
			}
		}
		strncpy(exstr, s_formatStr, sizeof(exstr)-1);
		n /= 1000;
	}
	return s_formatStr;
}