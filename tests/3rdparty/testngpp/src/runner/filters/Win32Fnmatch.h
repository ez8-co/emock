
#ifndef	__EVIL_FNMATCH_H__
#define	__EVIL_FNMATCH_H__

#include <testngpp/testngpp.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* We #undef these before defining them because some losing systems
   (HP-UX A.08.07 for example) define these in <unistd.h>.  */
#undef	FNM_PATHNAME
#undef	FNM_NOESCAPE
#undef	FNM_PERIOD

/* Bits set in the FLAGS argument to `fnmatch'.  */
#define	FNM_PATHNAME	(1 << 0) /* No wildcard can ever match `/'.  */
#define	FNM_NOESCAPE	(1 << 1) /* Backslashes don't quote special chars.  */
#define	FNM_PERIOD	(1 << 2) /* Leading `.' is matched only explicitly.  */

#if !defined (_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 2 || defined (_GNU_SOURCE)
#define	FNM_FILE_NAME	FNM_PATHNAME /* Preferred GNU name.  */
#define	FNM_LEADING_DIR	(1 << 3) /* Ignore `/...' after a match.  */
#define	FNM_CASEFOLD	(1 << 4) /* Compare without regard to case.  */
#endif

/* Value returned by `fnmatch' if STRING does not match PATTERN.  */
#define	FNM_NOMATCH   1
#define FNM_SYNTAXERR 2
#define FNM_NOMEM     3

/* Match STRING against the filename pattern PATTERN,
   returning zero if it matches, FNM_NOMATCH if not.  */
DLL_EXPORT int fnmatch(const char *__pattern, const char *__string, int __flags);

#ifdef	__cplusplus
}
#endif

#endif /* __EVIL_FNMATCH_H__ */

