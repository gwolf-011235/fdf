/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_message.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwolf <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:03:42 by gwolf             #+#    #+#             */
/*   Updated: 2023/01/26 18:00:08 by gwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERR_MESSAGE_H
# define ERR_MESSAGE_H

# define STRINGIFY_(x) #x
# define STRINGIFY(x) STRINGIFY_(x)

#define ERR_ARGS "❌ Wrong number of arguments - expected one"
#define ERR_OPEN "❌ Couldn't open file"
#define ERR_READ "❌ Parsing error, map is not correctly formatted"
#define ERR_MEM "❌ Memory not sufficient"
#define ERR_BIG "❌ Map too big. Max rows is " STRINGIFY(ROW_MAX)
#define ERR_CLOSE "❌ Couldn't close file"
#define ERR_LINE "❌ Lines don't have the same number of values"
#define ERR_EMPTY "❌ The map is empty"

#endif
