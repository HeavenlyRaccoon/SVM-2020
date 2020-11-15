#include "pch.h"
#include "Parm.h"
#include "Error.h"
namespace Parm {
	PARM getparm(int argc, char* argv[]) {
		bool check = false;
		PARM parm = { "null", "null", "null" };
		if (argc == 1) {
			throw ERROR_THROW(100);
		}
		if (argc > 4) {
			throw ERROR_THROW(109);
		}

		for (int i = 1; i < argc; i++)
			if (strstr(argv[i], PARM_IN)) check = true;
		if (!check) throw ERROR_THROW(100);

		for (int j = 1; j < argc; j++) {
			if (strstr(argv[j], PARM_IN)) {
				for (int i = 4, q = strlen(argv[j]); i < q; i++) {
					parm.in[i - 4] = argv[j][i];
				}
			}
			if (strstr(argv[j], PARM_OUT)) {
				for (int i = 5, q = strlen(argv[j]); i < q; i++) {
					parm.out[i - 5] = argv[j][i];
				}
			}
			if (strstr(argv[j], PARM_LOG)) {
				for (int i = 5, q = strlen(argv[j]); i < q; i++) {
					parm.log[i - 5] = argv[j][i];
				}
			}

		}

		if (strcmp(parm.out, "null") == 0) {
			for (int i = 0, size = strlen(parm.in); i < size; i++) {
				parm.out[i] = parm.in[i];
			}
			for (int i = 0, size = strlen(PARM_OUT_DEFAULT_EXT); i < size; i++) {
				parm.out[strlen(parm.out)] = PARM_OUT_DEFAULT_EXT[i];
			}
			parm.out[strlen(parm.out)] = '\0';
		}

		if (strcmp(parm.log, "null") == 0) {
			for (int i = 0, size = strlen(parm.in); i < size; i++) {
				parm.log[i] = parm.in[i];
			}
			for (int i = 0, size = strlen(PARM_LOG_DEFAULT_EXT); i < size; i++) {
				parm.log[strlen(parm.log)] = PARM_LOG_DEFAULT_EXT[i];
			}
			parm.log[strlen(parm.log)] = '\0';
		}

		return parm;
	}

}