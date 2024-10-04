#ifndef ASSEMBLY_FUNCTION_MACROS_H
#define ASSEMBLY_FUNCTION_MACROS_H

#ifdef ALIAS_ADD_LIBMIN
  #define ASM_FUNCTION_LABEL(name_without_libmin_prefix) \
    .global name_without_libmin_prefix; .type name_without_libmin_prefix, @function; \
    .global libmin_##name_without_libmin_prefix; .type libmin_##name_without_libmin_prefix, @function; \
    name_without_libmin_prefix: \
    libmin_##name_without_libmin_prefix:
#else

  #ifdef ADD_LIBMIN
    #define ASM_FUNCTION_LABEL(name_without_libmin_prefix) \
      .global libmin_##name_without_libmin_prefix; .type libmin_##name_without_libmin_prefix, @function; \
      libmin_##name_without_libmin_prefix:
  #else
    #define ASM_FUNCTION_LABEL(name_with_libmin_prefix) \
      .global name_with_libmin_prefix; .type name_with_libmin_prefix, @function; \
      name_with_libmin_prefix:
  #endif // ADD_LIBMIN

#endif // ALIAS_ADD_LIBMIN

#endif // ASSEMBLY_FUNCTION_MACROS_H
