/**
 * @filename :
 * 		test_glob.c
 * 
 * @note :
 * 		glob库函数用于Linux文件系统中路径名称的模式匹配，即查找文件系统中指定模式的路径。
 * 		注意，这不是正则表达式匹配，虽然有些相似，但还是有点差别。
 * 
 * 		./bin/test_glob "./*.cpp" "./*.h" "./make*" "~/p*l/p?ng"
 * 
 **/
#if 0
The glob() function searches for all the pathnames matching pattern according to the rules used by the shell (see glob(7)). No tilde expansion or parameter substitution is done; if you want these, use wordexp(3).

The globfree() function frees the dynamically allocated storage from an earlier call to glob().

The results of a glob() call are stored in the structure pointed to by pglob. This structure is of type glob_t (declared in <glob.h>) and includes the following elements defined by POSIX.2 (more may be present as an extension):

    typedef struct {
        size_t   gl_pathc;    /* Count of paths matched so far  */
        char   **gl_pathv;    /* List of matched pathnames.  */
        size_t   gl_offs;     /* Slots to reserve in gl_pathv.  */
    } glob_t;

Results are stored in dynamically allocated storage.

The argument flags is made up of the bitwise OR of zero or more the following symbolic constants, which modify the behavior of glob():
	GLOB_ERR
		Return upon a read error (because a directory does not have read permission, for example). By default, glob() attempts carry on despite errors, reading all of the directories that it can. 
	GLOB_MARK
		Append a slash to each path which corresponds to a directory. 
	GLOB_NOSORT
		Don't sort the returned pathnames. The only reason to do this is to save processing time. By default, the returned pathnames are sorted. 
	GLOB_DOOFFS
		Reserve pglob->gl_offs slots at the beginning of the list of strings in pglob->pathv. The reserved slots contain NULL pointers. 
	GLOB_NOCHECK
		If no pattern matches, return the original pattern. By default, glob() returns GLOB_NOMATCH if there are no matches. 
	GLOB_APPEND
		Append the results of this call to the vector of results returned by a previous call to glob(). Do not set this flag on the first invocation of glob(). 
	GLOB_NOESCAPE
		Don't allow backslash ('\') to be used as an escape character. Normally, a backslash can be used to quote the following character, providing a mechanism to turn off the special meaning metacharacters. 
	flags may also include any of the following, which are GNU extensions and not defined by POSIX.2:
	GLOB_PERIOD
		Allow a leading period to be matched by metacharacters. By default, metacharacters can't match a leading period. 
	GLOB_ALTDIRFUNC
		Use alternative functions pglob->gl_closedir, pglob->gl_readdir, pglob->gl_opendir, pglob->gl_lstat, and pglob->gl_stat for file system access instead of the normal library functions. 
	GLOB_BRACE
		Expand csh(1) style brace expressions of the form {a,b}. Brace expressions can be nested. Thus, for example, specifying the pattern "{foo/{,cat,dog},bar}" would return the same results as four separate glob() calls using the strings: "foo/", "foo/cat", "foo/dog", and "bar". 
	GLOB_NOMAGIC
		If the pattern contains no metacharacters then it should be returned as the sole matching word, even if there is no file with that name. 
	GLOB_TILDE
		Carry out tilde expansion. If a tilde ('~') is the only character in the pattern, or an initial tilde is followed immediately by a slash ('/'), then the home directory of the caller is substituted for the tilde. If an initial tilde is followed by a username (e.g., "~andrea/bin"), then the tilde and username are substituted by the home directory of that user. If the username is invalid, or the home directory cannot be determined, then no substitution is performed. 
	GLOB_TILDE_CHECK
		This provides behavior similar to that of GLOB_TILDE. The difference is that if the username is invalid, or the home directory cannot be determined, then instead of using the pattern itself as the name, glob() returns GLOB_NOMATCH to indicate an error. 
	GLOB_ONLYDIR
		This is a hint to glob() that the caller is interested only in directories that match the pattern. If the implementation can easily determine file-type information, then nondirectory files are not returned to the caller. However, the caller must still check that returned files are directories. (The purpose of this flag is merely to optimize performance when the caller is interested only in directories.) 
	If errfunc is not NULL, it will be called in case of an error with the arguments epath, a pointer to the path which failed, and eerrno, the value of errno as returned from one of the calls to opendir(3), readdir(3), or stat(2). If errfunc returns nonzero, or if GLOB_ERR is set, glob() will terminate after the call to errfunc.

Upon successful return, pglob->gl_pathc contains the number of matched pathnames and pglob->gl_pathv contains a pointer to the list of pointers to matched pathnames. The list of pointers is terminated by a NULL pointer.

It is possible to call glob() several times. In that case, the GLOB_APPEND flag has to be set in flags on the second and later invocations.

As a GNU extension, pglob->gl_flags is set to the flags specified, ored with GLOB_MAGCHAR if any metacharacters were found.

Return Value
On successful completion, glob() returns zero. Other possible returns are:

GLOB_NOSPACE
    for running out of memory, 
GLOB_ABORTED
    for a read error, and 
GLOB_NOMATCH
    for no found matches. 
#endif 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glob.h>

static int test_fun(int argc, char * argv[]);
static void print_gl(glob_t *gl);

int main(int argc, char *argv[]) {
    if (argc > 1) {
        test_fun(argc, argv);
    } else {
        printf("%s [\"STRING\"]...\n", argv[0]);
	}
	
    return 0;
}

static int test_fun(int argc, char *argv[]) {
    glob_t gl;
    int i;
    
    for(i = 1; i < argc; ++i) {
        gl.gl_offs = 0;
        glob(argv[i], GLOB_TILDE, 0, &gl);
        print_gl(&gl);
        globfree(&gl);
    }
    
    return 0;
}

static void print_gl(glob_t *gl) {
	unsigned int i;
	
    for(i = 0; i < gl->gl_pathc; ++i) {
        printf("%s\n", gl->gl_pathv[i]);
	}
	
    printf("++++++++++++++++++++++\n");
}  
