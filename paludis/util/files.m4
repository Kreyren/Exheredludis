dnl vim: set ft=m4 et :
dnl This file is used by Makefile.am.m4. You should use the provided
dnl autogen.bash script to do all the hard work.
dnl
dnl This file is used to avoid having to make lots of repetitive changes in
dnl Makefile.am every time we add a source or test file. The first parameter is
dnl the base filename with no extension; later parameters can be `hh', `cc',
dnl `gtest', `impl', `testscript'. Note that there isn't much error checking done
dnl on this file at present...

add(`accept_visitor',                    `hh')
add(`active_object_ptr',                 `hh', `cc', `fwd', `gtest')
add(`attributes',                        `hh')
add(`buffer_output_stream',              `hh', `cc', `fwd', `gtest')
add(`byte_swap',                         `hh', `gtest')
add(`channel',                           `hh', `cc')
add(`checked_delete',                    `hh')
add(`clone',                             `hh', `impl')
add(`config_file',                       `hh', `cc', `fwd', `se', `gtest', `testscript')
add(`condition_variable',                `hh', `cc', `gtest')
add(`cookie',                            `hh', `cc')
add(`create_iterator',                   `hh', `fwd', `impl', `gtest')
add(`damerau_levenshtein',               `hh', `cc', `gtest')
add(`destringify',                       `hh', `cc', `gtest')
add(`deferred_construction_ptr',         `hh', `cc', `fwd', `gtest')
add(`digest_registry',                   `hh', `cc')
add(`discard_output_stream',             `hh', `cc')
add(`elf',                               `hh', `cc')
add(`elf_dynamic_section',               `hh', `cc')
add(`elf_relocation_section',            `hh', `cc')
add(`elf_sections',                      `hh', `cc')
add(`elf_symbol_section',                `hh', `cc')
add(`elf_types',                         `hh')
add(`enum_iterator',                     `hh', `cc', `fwd', `gtest')
add(`env_var_names',                     `hh', `cc')
add(`exception',                         `hh', `cc')
add(`executor',                          `hh', `cc', `fwd')
add(`extract_host_from_url',             `hh', `cc', `fwd', `gtest')
add(`fd_holder',                         `hh')
add(`fs_iterator',                       `hh', `cc', `fwd', `se', `gtest', `testscript')
add(`fs_error',                          `hh', `cc')
add(`fs_path',                           `hh', `cc', `fwd', `se', `gtest', `testscript')
add(`fs_stat',                           `hh', `cc', `fwd', `gtest', `testscript')
add(`graph',                             `hh', `cc', `fwd', `impl', `gtest')
add(`hashes',                            `hh', `cc', `gtest')
add(`iterator_funcs',                    `hh', `gtest')
add(`indirect_iterator',                 `hh', `fwd', `impl', `gtest')
add(`is_file_with_extension',            `hh', `cc', `se', `gtest', `testscript')
add(`join',                              `hh', `gtest')
add(`log',                               `hh', `cc', `se', `gtest')
add(`make_named_values',                 `hh', `cc')
add(`make_null_shared_ptr',              `hh')
add(`make_shared_copy',                  `hh', `fwd')
add(`map',                               `hh', `fwd', `impl', `cc')
add(`member_iterator',                   `hh', `fwd', `impl', `gtest')
add(`md5',                               `hh', `cc', `gtest')
add(`mutex',                             `hh', `cc', `fwd', `gtest')
add(`named_value',                       `hh', `cc', `fwd')
add(`no_type',                           `hh')
add(`operators',                         `hh')
add(`options',                           `hh', `fwd', `cc', `gtest')
add(`pimp',                              `hh', `impl')
add(`pipe',                              `hh', `cc')
add(`pool',                              `hh', `cc', `impl', `gtest', `fwd')
add(`pretty_print',                      `hh', `cc', `gtest')
add(`process',                           `hh', `cc', `fwd', `gtest', `testscript')
add(`pty',                               `hh', `cc', `gtest')
add(`realpath',                          `hh', `cc', `gtest', `testscript')
add(`remove_shared_ptr',                 `hh')
add(`return_literal_function',           `hh', `cc', `fwd', `gtest')
add(`rmd160',                            `hh', `cc', `gtest')
add(`safe_ifstream',                     `hh', `cc', `fwd', `gtest', `testscript')
add(`safe_ofstream',                     `hh', `cc', `gtest', `testscript')
add(`save',                              `hh', `gtest')
add(`sequence',                          `hh', `fwd', `impl', `cc')
add(`set',                               `hh', `fwd', `impl', `cc')
add(`sha1',                              `hh', `cc', `gtest')
add(`sha256',                            `hh', `cc', `gtest')
add(`sha512',                            `hh', `cc', `gtest')
add(`simple_parser',                     `hh', `cc', `gtest', `fwd')
add(`singleton',                         `hh', `impl', `gtest')
add(`stream_holder',                     `hh')
add(`stringify',                         `hh', `gtest')
add(`string_list_stream',                `hh', `cc', `fwd', `gtest')
add(`strip',                             `hh', `cc', `gtest')
add(`system',                            `hh', `cc', `gtest')
add(`tail_output_stream',                `hh', `cc', `fwd', `gtest')
add(`tee_output_stream',                 `hh', `cc', `fwd')
add(`thread',                            `hh', `cc', `gtest')
add(`thread_pool',                       `hh', `cc', `gtest')
add(`timestamp',                         `hh', `cc', `fwd')
add(`tokeniser',                         `hh', `cc', `gtest')
add(`tribool',                           `hh', `cc', `fwd', `gtest')
add(`type_list',                         `hh', `cc', `fwd')
add(`upper_lower',                       `hh', `cc')
add(`util',                              `hh')
add(`visitor',                           `hh', `cc', `fwd', `impl')
add(`visitor_cast',                      `hh', `cc', `fwd')
add(`whirlpool',                         `hh', `cc', `gtest')
add(`wildcard_expander',                 `hh', `cc', `gtest', `testscript')
add(`wrapped_forward_iterator',          `hh', `fwd', `impl', `gtest')
add(`wrapped_output_iterator',           `hh', `fwd', `impl')
add(`wrapped_value',                     `hh', `fwd', `impl', `gtest')

