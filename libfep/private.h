/*
 * Copyright (C) 2012 Daiki Ueno <ueno@unixuser.org>
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __LIBFEP_PRIVATE_H__
#define __LIBFEP_PRIVATE_H__

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "xalloc.h"
#include "xvasprintf.h"
#include "xstrndup.h"
#include "minmax.h"
#include <libfep/libfep.h>

#ifndef BUFSIZ
#define BUFSIZ 4096
#endif

#define SIZEOF(array) (sizeof((array)) / sizeof((array)[0]))

/* string.c */
struct _FepString {
  char *str;
  size_t len;
  size_t cap;
};
typedef struct _FepString FepString;

void    _fep_string_append (FepString  *buf,
                            const char *str,
                            size_t      count);
void    _fep_string_append_c
                           (FepString  *buf,
			    char        c);
void    _fep_string_clear  (FepString  *buf);
void    _fep_string_copy   (FepString  *dst,
                            FepString  *src);
char ** _fep_strsplit      (const char *str,
                            const char *delimiter,
                            int         max_tokens);
char ** _fep_strsplit_set  (const char *str,
                            const char *delimiter,
                            int         max_tokens);
char *  _fep_strjoinv      (char      **strv,
                            const char *delimiter);
size_t  _fep_strv_length   (char      **strv);
void    _fep_strfreev      (char      **strv);
int     _fep_strwidth      (const char *str);
char *  _fep_strtrunc      (const char *str,
                            int         width);
int     _fep_charcount     (const char *str);
char *  _fep_substring     (const char *str,
                            int         from,
                            int         to);

/* list.c */
struct _FepList
{
  struct _FepList *prev, *next;
  void *data;
};
typedef struct _FepList FepList;

FepList *_fep_list_append (FepList *head, void *data);

/* control.c */
/* Note that each control message from server to client has return
   value, while the opposite does not.

   See _fep_dispatch_control_message in fep/control.c for server and
   fep_client_dispatch in libfep/client.c for client handling. */
typedef enum
  {
    /* client to server */
    FEP_CONTROL_SET_CURSOR_TEXT = 1,
    FEP_CONTROL_SET_STATUS_TEXT = 2,
    FEP_CONTROL_SEND_TEXT = 3,
    FEP_CONTROL_SEND_DATA = 4,
    FEP_CONTROL_FORWARD_KEY_EVENT = 5,
    /* server to client */
    FEP_CONTROL_KEY_EVENT = 6,
    FEP_CONTROL_RESIZE_EVENT = 7,
    /* response from client */
    FEP_CONTROL_RESPONSE = 8
  } FepControlCommand;

struct _FepControlMessage
{
  FepControlCommand command;
  FepString *args;
  size_t n_args;
};
typedef struct _FepControlMessage FepControlMessage;

int      _fep_read_control_message               (int                 fd,
                                                  FepControlMessage  *message);
int      _fep_write_control_message              (int                 fd,
                                                  FepControlMessage  *message);
FepList *_fep_append_control_message             (FepList            *head,
                                                  FepControlMessage  *message);
void     _fep_control_message_alloc_args         (FepControlMessage  *message,
                                                  size_t              n_args);
void     _fep_control_message_free_args          (FepControlMessage  *message);
void     _fep_control_message_free               (FepControlMessage  *message);
int      _fep_control_message_read_uint32_arg    (FepControlMessage  *message,
                                                  off_t               index,
                                                  uint32_t           *r_val);
int      _fep_control_message_write_uint32_arg   (FepControlMessage  *message,
                                                  off_t               index,
                                                  uint32_t            val);
int      _fep_control_message_write_uint8_arg    (FepControlMessage  *message,
                                                  off_t               index,
                                                  uint8_t             val);
int      _fep_control_message_write_string_arg   (FepControlMessage  *message,
                                                  off_t               index,
                                                  const char         *str,
                                                  size_t              length);
int      _fep_control_message_read_attribute_arg (FepControlMessage  *message,
                                                  off_t               index,
                                                  FepAttribute       *r_attr);
int      _fep_control_message_write_attribute_arg (FepControlMessage  *message,
                                                   off_t               index,
                                                   const FepAttribute *attr);

#endif	/* __LIBFEP_PRIVATE_H__ */
