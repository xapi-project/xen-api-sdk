/*
 * Copyright (c) Citrix Systems, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *   1) Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *   2) Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials
 *      provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef XEN_INTERNAL_H
#define XEN_INTERNAL_H


#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

#include <xen/api/xen_common.h>


enum abstract_typename
{
  VOID,
  STRING,
  INT,
  FLOAT,
  BOOL,
  DATETIME,
  SET,
  MAP,
  STRUCT,
  REF,
  ENUM,
  ENUMSET
};


typedef struct
{
    size_t size;
    void *contents[];
} arbitrary_set;


typedef struct struct_member struct_member;


typedef struct abstract_type
{
    enum abstract_typename typename;
    const struct abstract_type *child;
    const char * (*enum_marshaller)(int);
    int (*enum_demarshaller)(xen_session *, const char *);
    size_t struct_size;
    size_t member_count;
    const struct_member *members;
} abstract_type;


struct struct_member
{
    const char *key;
    const struct abstract_type *type;
    int offset;
};


extern const abstract_type abstract_type_string;
extern const abstract_type abstract_type_int;
extern const abstract_type abstract_type_float;
extern const abstract_type abstract_type_bool;
extern const abstract_type abstract_type_datetime;
extern const abstract_type abstract_type_ref;

extern const abstract_type abstract_type_string_set;
extern const abstract_type abstract_type_ref_set;
extern const abstract_type abstract_type_int_set;

extern const abstract_type abstract_type_string_int_map;
extern const abstract_type abstract_type_string_string_map;
extern const abstract_type abstract_type_string_ref_map;
extern const abstract_type abstract_type_int_float_map;
extern const abstract_type abstract_type_int_int_map;
extern const abstract_type abstract_type_int_string_set_map;

extern const abstract_type abstract_type_string_string_set_map;
extern const abstract_type abstract_type_string_string_string_map_map;

extern const abstract_type xen_vdi_nbd_server_info_record_set_abstract_type_;


typedef struct abstract_value
{
    const abstract_type *type;
    union
    {
        const char *string_val;
        int64_t int_val;
        int enum_val;
        double float_val;
        bool bool_val;
        arbitrary_set *set_val;
        void *struct_val;
        time_t datetime_val;
    } u;
} abstract_value;


extern void
xen_call_(xen_session *s, const char *method_name, abstract_value params[],
          int param_count, const abstract_type *result_type, void *value);


#define XEN_CALL_(method_name__)                                \
    xen_call_(session, method_name__, param_values,             \
              sizeof(param_values) / sizeof(param_values[0]),   \
              &result_type, result)                             \


extern char *
xen_strdup_(const char *in);


extern int
xen_enum_lookup_(const char *str, const char **lookup_table, int n);

#define ENUM_LOOKUP(str__, lookup_table__)      \
    xen_enum_lookup_(str__, lookup_table__,     \
                     sizeof(lookup_table__) /   \
                     sizeof(lookup_table__[0])) \

#define XEN_ALLOC(type__)                       \
type__ *                                        \
type__ ## _alloc()                              \
{                                               \
    return calloc(1, sizeof(type__));           \
}                                               \


#define XEN_FREE(type__)                        \
void                                            \
type__ ## _free(type__ handle)                  \
{                                               \
    free(handle);                               \
}                                               \


#define XEN_SET_ALLOC_FREE(type__)              \
    XEN_SET_ALLOC(type__)                       \
    XEN_SET_FREE(type__)


#define XEN_SET_ALLOC(type__)                                           \
type__ ## _set *                                                        \
type__ ## _set_alloc(size_t size)                                       \
{                                                                       \
    type__ ## _set *result = calloc(1, sizeof(type__ ## _set) +         \
                                    size * sizeof(type__));             \
    result->size = size;                                                \
    return result;                                                      \
}


#define XEN_SET_FREE(type__)                                            \
void type__ ## _set_free(type__ ## _set *set)                           \
{                                                                       \
    if (set == NULL)                                                    \
        return;                                                         \
    for (size_t i = 0; i < set->size; i++)                              \
       type__ ## _free(set->contents[i]);                               \
    free(set);                                                          \
}


#define XEN_RECORD_OPT_FREE(type__)                                     \
void type__ ## _record_opt_free(type__ ## _record_opt *opt) {           \
    if (opt == NULL) return;                                            \
    if (opt->is_record)                                                 \
        type__ ## _record_free(opt->u.record);                          \
    else                                                                \
        type__ ## _free(opt->u.handle);                                 \
    free(opt);                                                          \
}


#endif
