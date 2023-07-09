#include "../minishell.h"
#include <dirent.h>

void ft_calcule_etoile(char *data, int *i)
{
    int j;

    j = 0;
    while (data[j] != '\0')
    {
        if (data[j] == '\'' || data[j] == '\"')
            j = skip_quote(data, j);
        if (data[j] == '*' && data[j + 1] != '*')
            (*i)++;
        j++;
    }
}

DIR *opdir(t_parser *parser)
{
    DIR *OPENFILE;
    t_env *env;
    env = parser->lex->env;
    while (env)
    {
        if (ft_strcmp("PWD", env->key) == 0)
            break;
        env = env->next;
    }
    if ((OPENFILE = opendir(env->value)) == NULL)
    {
        perror("opendir() error");
        return (NULL);
    }
    return (OPENFILE);
}

// int ft_check_derectory(char *entry_name ,int j, DIR *OPENFILE, t_parser *parser) // kanat hnya j zayda 
// {
//     t_env *env;
//     struct dirent *entry;
//     int i;
//     int count;
//     char *pwd;
//     (void)j;

//     env = parser->lex->env;
//     i = 0;
//     count = 0;
//     while (env)
//     {
//         if (strcmp("PWD", env->key) == 0)
//             break;
//         env = env->next;
//     }
//     pwd = ft_strdup(env->value);
//     pwd = ft_strjoin(pwd, "/");
//     pwd = ft_strjoin(pwd, entry_name);
//     if ((OPENFILE = opendir(pwd)) == NULL)
//         return (0);
//     while ((entry = readdir(OPENFILE)) != NULL)
//     {
//         if (ft_strcmp(entry->d_name, "..") != 0 && ft_strcmp(entry->d_name, ".") != 0 
//             && entry->d_name[0] != '.' )
//             count++;
//         i++;
//     }
//     return (count);
// }

int count_nb_newdt(int *nb_w, int i)
{
    int j;
    int nb;

    j = 0;
    nb = 0;
    while (j < i)
    {
        if (nb_w[j] == 1)
            nb++;
        j++;
    }
    return (nb);
}

int check_valid_first(char *entry_name, char *patern)
{
    char *patern_entry;

    patern_entry = ft_substr(entry_name, 0, ft_strlen(patern));
    if (!patern_entry)
        exit(1);
    if (ft_strcmp(patern_entry, patern) == 0)
    {
        free(patern_entry);
        return (1);
    }
    free(patern_entry);
    return (0);
}

int check_valid_last(char *entry_name, char *patern)
{
    char *patern_entry;

    patern_entry = ft_substr(entry_name, ft_strlen(entry_name) - ft_strlen(patern), ft_strlen(entry_name)); // !!!!!!!!!!!!!!!!!
    if (!patern_entry)
        exit(1);
    if (ft_strcmp(patern_entry, patern) == 0)
    {
        free(patern_entry);
        return (1);
    }
    free(patern_entry);
    return (0);
}

int *find_first_list_patern(t_parser *parser, int *nb_w, char **patern)
{
    int j;
    DIR *OPENFILE;
    struct dirent *entry;

    j = 0;
    if ((OPENFILE = opdir(parser)) == NULL)
        return (NULL);
    while ((entry = readdir(OPENFILE)) != NULL)
    {
        if (check_valid_first(entry->d_name, patern[0]) == 1 && check_valid_last(entry->d_name, patern[1]) == 1 && ft_strlen(entry->d_name) >= ft_strlen(patern[0]) + ft_strlen(patern[1])) // ft_strcmp(patern_entry[0], patern[0]) == 0 && ft_strcmp(patern_entry[1], patern[1]) == 0)   
            nb_w[j] = 1;
        else
            nb_w[j] = 0;
        // ft_printf ("%d %s\n", nb_w[j], entry->d_name);
        j++;
    }
    // free patern !!!!!!
    return (nb_w);
}


int check_position_etoile(char *data, char c)
{
    if (c == 'o')
    {
        if (data[0] == '*')
            return (1);
        else if (data[ft_strlen(data)])
            return (2);
    }
    else
    {
        if (data[0] != '*' && data[ft_strlen(data) - 1] != '*')
            return (1);
        else if (data[0] != '*' && data[ft_strlen(data) - 1] == '*')
            return (2);
        else if (data[0] == '*' && data[ft_strlen(data) - 1] != '*')
            return (3);
        else if (data[0] == '*' && data[ft_strlen(data) - 1] == '*')
            return (4);
    }
    return (0);
}

int *find_patern_one_etoile(t_parser *parser, int *nb_w, char c, char **patern)
{
    // char *patern_entry;
    int j;
    DIR *OPENFILE;
    struct dirent *entry;

    j = 0;
    if ((OPENFILE = opdir(parser)) == NULL)
        return (NULL);
    if (c == 'f')
    {
        while ((entry = readdir(OPENFILE)) != NULL)
        {
            if (check_valid_first(entry->d_name, patern[0]) == 1)
                nb_w[j] = 1;
            else
                nb_w[j] = 0;
            j++;
        }
        // free patern
    }
    else if (c == 'l')
    {
        while ((entry = readdir(OPENFILE)) != NULL)
        {
            // patern_entry = ft_substr(entry->d_name, ft_strlen(entry->d_name) - ft_strlen(patern[0]), ft_strlen(entry->d_name));
            if (check_valid_last(entry->d_name, patern[0]) == 1 /*ft_strcmp(patern_entry, patern[0]) == 0*/)
                nb_w[j] = 1;
            else
                nb_w[j] = 0;
            j++;
            // free(patern_entry);
        }
        // free patern
    }
    return (nb_w);
}

char *find_entry_center(char *entry_name, char *patern, char *last_patern, char k)
{
    char *entry_center;
    int i;
    int j;
    int c;

    i = 0;
    entry_center = NULL;
    // j = ft_strlen (patern);
    while (entry_name[i] != '\0')
    {
        if (entry_name[i] == patern[0])
        {
            j = 1;
            i++;
            c = i;
            while (patern[j] != '\0')
            {
                if (patern[j] == entry_name[i])
                {
                    j++;
                    i++;
                }
                else
                    break;
            }
            if (patern[j] == '\0')
                break;
        }
        i++;
    }
    if (patern[j] == '\0' && (k == 'p' || k == 'l'))
        entry_center = ft_substr(entry_name, c, (ft_strlen(entry_name) - ft_strlen(last_patern) - c));
    else if (patern[j] == '\0' && (k == 'f' || k == 'n'))
        entry_center = ft_substr(entry_name, c, (ft_strlen(entry_name) - c));
    free(entry_name);
    return (entry_center);
}

int lenght_patern(char **patern)
{
    int i;

    i = 0;
    while (patern[i] != NULL)
        i++;
    return (i);
}

int *find_mult_etoile(t_parser *parser, int *nb_w, char *data, char **patern)
{
    int j;
    int i;
    char *entry_center;
    DIR *OPENFILE;
    struct dirent *entry;

    j = 0;
    i = 0;
    entry_center = NULL;
    if ((OPENFILE = opdir(parser)) == NULL)
        return (NULL);
    while ((entry = readdir(OPENFILE)) != NULL)
    {
        if (check_position_etoile(data, 'm') == 1)
        {
            if (check_valid_first(entry->d_name, patern[0]) == 1 && check_valid_last(entry->d_name, patern[lenght_patern(patern) - 1]) == 1 && ft_strlen(entry->d_name) >= ft_strlen(patern[0]) + ft_strlen(patern[lenght_patern(patern) - 1])) // ft_strcmp(patern_entry[0], patern[0]) == 0 && ft_strcmp(patern_entry[1], patern[1]) == 0)
            {
                entry_center = ft_substr(entry->d_name, ft_strlen(patern[0]), ft_strlen(entry->d_name) - ft_strlen(patern[lenght_patern(patern) - 1]) - ft_strlen(patern[0])); // na9anh 3la hsab ftali mital minishell.c m*s*.c 11 - 2 = 9 ghadi dakhlna hta na9ta m3aha ohna mabghinahach
                // ft_printf ("%s %d %d\n", entry_center, ft_strlen(patern[lenght_patern(patern) - 1]), ft_strlen(entry->d_name));
                i = 1;
                while (i < lenght_patern(patern) - 1)
                {
                    if (ft_strnstr(entry_center, patern[i]) == 1)
                    {
                        nb_w[j] = 0;
                        free(entry_center);
                        break;
                    }
                    // free(entry_center);
                    entry_center = find_entry_center(entry_center, patern[i], patern[lenght_patern(patern) - 1], 'p');
                    i++;
                }
                if (i == lenght_patern(patern) - 1)
                {
                    nb_w[j] = 1;
                }
            }
            else
                nb_w[j] = 0;
            //  ft_printf ("%d %s\n", nb_w[j], entry->d_name);
        }
        else if (check_position_etoile(data, 'm') == 2)
        {
            if (check_valid_first(entry->d_name, patern[0]) == 1 && ft_strlen(patern[0]) < ft_strlen(entry->d_name))
            {
                entry_center = ft_substr(entry->d_name, ft_strlen(patern[0]), ft_strlen(entry->d_name) - ft_strlen(patern[0])); // khasni nt2akad mn lenght
                // ft_printf ("%s\n", entry_center);
                i = 0;
                while (i < lenght_patern(patern))
                {
                    if (ft_strnstr(entry_center, patern[i]) == 1)
                    {
                        nb_w[j] = 0;
                        free(entry_center);
                        break;
                    }
                    entry_center = find_entry_center(entry_center, patern[i], patern[lenght_patern(patern) - 1], 'f');
                    i++;
                }
                if (i == lenght_patern(patern))
                    nb_w[j] = 1;
            }
            else
                nb_w[j]= 0;
        }
        else if (check_position_etoile(data, 'm') == 3)
        {
            if (check_valid_last(entry->d_name, patern[lenght_patern(patern) - 1]) == 1 && ft_strlen(patern[lenght_patern(patern) - 1]) < ft_strlen(entry->d_name))
            {
                entry_center = ft_substr(entry->d_name, 0, ft_strlen(entry->d_name) - ft_strlen(patern[lenght_patern(patern) - 1]));
                i = 0;
                while (i < lenght_patern(patern) - 1)
                {
                    if (ft_strnstr(entry_center, patern[i]) == 1)
                    {
                        nb_w[j] = 0;
                        free(entry_center);
                        break;
                    }
                    entry_center = find_entry_center(entry_center, patern[i], patern[lenght_patern(patern) - 1], 'l');
                    i++;
                }
                if (i == lenght_patern(patern) - 1)
                {
                    nb_w[j] = 1;
                }
            }
            else
                nb_w[j] = 0;
        }
        else if (check_position_etoile(data, 'm') == 4)
        {
            entry_center = ft_strdup(entry->d_name);
            i = 0;
            while (i < lenght_patern(patern))
            {
                if (ft_strnstr(entry_center, patern[i]) == 1)
                {
                    nb_w[j] = 0;
                    free(entry_center);
                    break;
                }
                // free(entry_center);
                entry_center = find_entry_center(entry_center, patern[i], patern[lenght_patern(patern) - 1], 'n');
                i++;
            }
            if (i == lenght_patern(patern)) // hna khasak t2akad 3lch madrtch else !!!!!!!!
                nb_w[j] = 1;
            // ft_printf ("%d %s\n", nb_w[j], entry->d_name);
        }
        j++;
    }
    return (nb_w);
}

char **handal_quote(char **patern)
{
    char *new_pa;
    int i;
    int j;

    i = 0;
    while (patern[i] != NULL)
    {
        new_pa = NULL;
        j = 0;
        while (patern[i][j] != '\0')
        {
            if (patern[i][j] == '\'' || patern[i][j] == '\"')
                new_pa = if_quote_fill(patern[i], &j, new_pa);
            else
                new_pa = ft_copier(patern[i][j], new_pa);
            j++;
        }
        // ft_printf ("%d %s\n", i, new_pa);
        free(patern[i]);
        patern[i] = ft_strdup(new_pa);
        free(new_pa);
        i++;
    }
    return (patern);
}

int *ft_tout_file(int *nb_w, DIR *OPENFILE, t_parser *parser)
{
    struct dirent *entry;
    int j;

    j = 0;
    if ((OPENFILE = opdir(parser)) == NULL)
        return (NULL);
    else   
    {
        while ((entry = readdir(OPENFILE)) != NULL)
        {
            if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0 
                || entry->d_name[0] == '.')
                nb_w[j] = 0;
            else
                nb_w[j] = 1;
            j++;
        }
    }
    return (nb_w);
}

int *check_exict_patern(t_parser *parser, char *data, int *nb_w, DIR *OPENFILE) //knt fiiha DIR *OPENFILE
{
    int i;
    int j;
    int nb_arg;
    char **patern;
    char *co_data;
    (void)OPENFILE;

    i = 0;
    j = 0;
    nb_arg = 0;
    ft_calcule_etoile(data, &i);
    co_data = ft_strdup(data);
    while (co_data[j] != '\0')
    {
        if (co_data[j] == '\'' || co_data[j] == '\"')
            j = skip_quote(co_data, j);
        else if (co_data[j] == '*')
            co_data[j] = '\n';
        j++;
    }
    patern = ft_split(co_data, '\n', &nb_arg);
    patern = handal_quote(patern);
    if (i == 1)
    {
        if (nb_arg == 1)
        {
            if (check_position_etoile(data, 'o') == 1)
                nb_w = find_patern_one_etoile(parser, nb_w, 'l', patern);
            else if (check_position_etoile(data, 'o') == 0)
                nb_w = find_patern_one_etoile(parser, nb_w, 'f', patern);
        }
        else if (nb_arg == 2)
            nb_w = find_first_list_patern(parser, nb_w, patern);
        else
            nb_w = ft_tout_file(nb_w, OPENFILE, parser);
    }
    else
        nb_w = find_mult_etoile(parser, nb_w, data, patern);
    free(co_data);
    return (nb_w);
}

t_data *cop_current_dt(t_cmd *cmd, int j, int *nb_w, int i)
{
    int nb;
    t_data *new_dt;
    int k;

    nb = count_nb_newdt(nb_w, i);
    k = 0;
    new_dt = NULL;
    if (nb >= 1)
    {
        new_dt = malloc(sizeof(t_data) * (cmd->dt_nb + nb - 1));
        if (!new_dt)
            exit(1);
        while (k < cmd->dt_nb)
        {
            if (k != j)
            {
                new_dt[k].data = ft_strdup(cmd->dt[k].data);
                free(cmd->dt[k].data);
                new_dt[k].copy_data = ft_strdup(cmd->dt[k].copy_data);
                free(cmd->dt[k].copy_data);
                new_dt[k].ex_dollar = cmd->dt[k].ex_dollar;
                new_dt[k].name = cmd->dt[k].name;
            }
            k++;
        }
        free(cmd->dt[j].data);
        free(cmd->dt[j].copy_data);
    }
    else if (nb == 0)
        return (cmd->dt);
    return (new_dt);
}


t_data *fill_wildcard_data(t_parser *parser, t_cmd *cmd, int j, int *nb_w)
{
    DIR *OPENFILE;
    struct dirent *entry;
    int i;
    int check;
    int x;

    i = 0;
    check = 0;
    if ((OPENFILE = opdir(parser)) == NULL)
        exit(1);
    else  
    {
        x = cmd->dt_nb - 1;
        while ((entry = readdir(OPENFILE)) != NULL)
        {
            if (nb_w[i] == 1)
            {
                if (check == 0)
                {
                    check++;
                    cmd->dt[j].data = ft_strdup(entry->d_name);
                    cmd->dt[j].copy_data =  ft_strdup(entry->d_name);
                    cmd->dt[j].ex_dollar = 0;
                    cmd->dt[j].name = 1;
                }
                else 
                {
                    cmd->dt[x].data = ft_strdup(entry->d_name);
                    cmd->dt[x].copy_data =  ft_strdup(entry->d_name);
                    cmd->dt[x].ex_dollar = 0;
                    cmd->dt[x].name = 1;
                } 
                x++;
            }
            i++;
        }
    }
    return (cmd->dt);
}

t_data *fill_wil_in_cmd(t_parser *parser, char *data, t_cmd *cmd, int j)
{
    DIR *OPENFILE;
    struct dirent *entry;
    int i;
    int *nb_w;

    i = 0;
    if ((OPENFILE = opdir(parser)) == NULL)
        exit(1); // exit status
    else
    {
        while ((entry = readdir(OPENFILE)) != NULL)
            i++;
        closedir(OPENFILE);
    }
    nb_w = malloc(sizeof(int *) * i);
    if (!nb_w)
        exit(1); // exit status
    nb_w = check_exict_patern(parser, data, nb_w, OPENFILE);
    // int y = 0;
    // while (y < i)
    // {
    //     ft_printf("%d\n", nb_w[y]);
    //     y++;
    // }
    cmd->dt = cop_current_dt(cmd, j, nb_w, i);
    if (count_nb_newdt(nb_w, i) != 0)
    {
        cmd->dt = fill_wildcard_data(parser, cmd, j, nb_w);// x = (cmd->dt_nb  - 1); //hna hnaya nb dt badi mn wahd oana baghi rad x l zero 3lach dart -2 omachi ghi wahad
        cmd->dt_nb += count_nb_newdt(nb_w, i) - 1;
    }
    return (cmd->dt);
}
void handal_wildcard(t_parser *parser, t_cmd *cmd)
{
    int j;
    int i;
    // int *nb_w;

    j = 0;
    i = 0;
    // ft_printf (" xxxx %d\n", current_nb_dt);
        while (j < cmd->dt_nb)
        {
            i = 0;

            while (cmd->dt[j].data != NULL && cmd->dt[j].data[i] != '\0')
            {
                if (cmd->dt[j].data[i] == '\'' || cmd->dt[j].data[i] == '\"')
                    i = skip_quote(cmd->dt[j].data, i);
                if (cmd->dt[j].data[i] == '*')
                    break;
                i++;
            }
            if ( cmd->dt[j].data != NULL &&cmd->dt[j].data[i] == '*')
            {
                cmd->dt = fill_wil_in_cmd(parser, cmd->dt[j].data, cmd, j); // freeeeeeeeeeeee nb_w 3ndek tansah yajadk hhhh
                // int x = 0;
                // while (x < 11)
                //     ft_printf ("%d\n", nb_w[x++]);
                // ft_printf("********************************************\n");
            }
            j++;
        }
    // if (j < cmd->dt_nb)
    // {
    //     nb_w = fill_wil_in_cmd(parser, cmd->dt[j].data, cmd, i);
    // }
}