#include "l10n.h"

#include "error.h"

char*
getError(uint32_t errorno)
{
	switch (errorno) {
	case ERROR_NO_ERROR:
		return (char*) _("There's no error");
	case ERROR_INVALID_OPTION:
		/* Since getopt() show message itself, we leave message empty */
		return (char*) "";
	case ERROR_MULTI_OPERATION:
		return (char*) _("Ambiguous operation options, please don't "
			"mix different operations in one command");
	case ERROR_NOT_ENOUGH_INPUT:
	case ERROR_TOO_MUCH_INPUT:
		return (char*) _("You need exactly four input files to "
				 "process");
	case ERROR_TEX_LOAD_FAILED:
		return (char*) _("Failed to load file");
	default:
		return (char*) _("Can not find corresponded error message, "
			"please file a bug to developers, thanks!");
	}
}
