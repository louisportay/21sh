#ifndef ENVIRON_H
# define ENVIRON_H

# include <termios.h>
# include <sys/syslimits.h>

# include "kvp.h"
# include "ft_hashset.h"

# define HASH_SIZE 91
# define HASH_PRIME 17

typedef struct s_env	t_env;

struct					s_env
{
	pid_t				pid;
	pid_t				pgid;
	int					fd;
	struct termios		told;
	struct termios		tnew;
	t_kvp				*env;
	t_kvp				*locals;
	int					istty;
	char				**path;
	t_hash_dict			*hash;
};

int						env_setup(t_env *env, char **environ);

char					*env_path_get(char *exe, char **pathes);
int						get_path(char *exe, t_env *env, char **path);


#endif
