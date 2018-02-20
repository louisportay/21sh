#include "ft_21sh.h"

int					ft_export(t_proc *p, t_ctx *ctx)
{
    return (modenv(p, ctx, "export"));
}

int					ft_setenv(t_proc *p, t_ctx *ctx)
{
    return (modenv(p, ctx, "setenv"));
}
