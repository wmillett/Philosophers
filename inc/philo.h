/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmillett <wmillett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:06:52 by wmillett          #+#    #+#             */
/*   Updated: 2023/10/19 14:44:06 by wmillett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//debug  --------------------
// extern int DEBUG;
//librairies ----------------
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
//general definitions -------
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define ERROR2 -2
# define SUCCESS 1
# define FAILURE 0
# define INVALID -1
# define FINISH 1
# define DONE 0
# define NOT_FINISH 0
//definitions for philo ------
# define EAT 1
# define SLEEP 2
# define THINK 3
# define WAIT_TO_EAT 4
# define WAIT_TO_SLEEP 5
# define TAKE 4
# define DIED 5
# define TAKE_ONE 6
# define TAKE_TWO 7
# define HAS_NOT 0
# define HAS_FORK 1
# define ALIVE 0
# define DEAD 1
# define NO_DIF -1
//error ----------------------
# define ATOL_ER -2147483650
# define NOINT_ER -2147483651
# define MIN_ER 3
# define MAX_ER 4
# define INT_ER 5
# define TEST 100
# define THREAD_ERR "Failed to create a thread."
# define MUTEX_ERR "Failed to initialize mutex."
# define ARG_NB_ERR "Wrong number of arguments."
# define FORMAT_ERR "Invalid argument format."
# define MEM_ERR "Memory allocaton failed."
# define ATOL_ERR "Argument does not fit in an integer."
# define MIN_ERR "Argument limit is too low: must be at least 60."
# define MAX_ERR "Argument for 'number of philosophers' is over 200."
//structs --------------------

typedef struct s_fork
{
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_amigo
{
	pthread_mutex_t	*fork;
}					t_amigo;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				action;
	uint64_t		action_start;
	uint64_t		start_time;
	int				nb_to_eat;
	pthread_mutex_t	action_lock;
	t_fork			own;
	t_amigo			friend;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	last_lock;
}					t_philo;

typedef struct s_program
{
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				nb_philos;
	int				to_eat;
	bool			mflag;
	int				mflag_data;
	int				mflag_fork;
	int				mflag_action;
	int				mflag_meal;
	pthread_t		reaper_thread;
	bool			dead_flag;
	int				start_flag;
	pthread_mutex_t	start_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	last_lock;
	t_philo			philos[200];
}					t_program;

typedef struct s_param
{
	union			u_param
	{
		struct		s_params
		{
			int		nb_philos;
			int		time_eat;
			int		time_sleep;
			int		time_die;
			int		nb_meals;
		} s_params;
		int			param[5];
	} u_param;
}					t_param;

//error --------------------
int					printerror(char *str);
int					escape(void *a, void *b, void *c, char *err_msg);
int					leave(void *a, void *b, void *c, uint64_t time);
//parse --------------------
int					check_arg(int argc, char **argv);
//utils_parse --------------
int					ft_isdigit(int nb);
int					ft_isspace(char c);
long				ft_atoil(const char *str);
//print ---------------------
void				printt(uint64_t start);
int					printm(int philo, int action, uint64_t start);
void				print_action(t_philo *philos, int action);
void				print_mutex(t_philo *philos, bool mutex);
//time -----------------------
bool				is_dead(void);
uint64_t			now(void);
uint64_t			timedif(int id);
void				set_start_time(t_param *params);
int					ready_start(t_philo *philos);
void				ft_sleep(uint64_t sleep, t_philo *philo);
void				ft_usleep(int sleep);
//utils_mem -----------------------
int					check_malloc(void *a, void *b, void *c, int type);
t_program			*data(void);
//routine --------------------------
int					multiple_philo(t_param *params);
void				*routine(void *info);
//one_philo -------------------------
int					one_philo(void *info);
int					set_one_philo(void);
//init_data -------------------------
void				wait_threads(void);
int					set_philo(t_param *param);
//mutex ------------------------------
int					init_mutex(t_param *params);
void				destroy_mutex(void);
//death ------------------------------
void				*the_reaper(void);
bool				is_dead(void);
bool				murder_philo(t_philo *philos);
#endif