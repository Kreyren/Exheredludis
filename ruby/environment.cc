/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2006 Ciaran McCreesh <ciaranm@ciaranm.org>
 *
 * This file is part of the Paludis package manager. Paludis is free software;
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License version 2, as published by the Free Software Foundation.
 *
 * Paludis is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <paludis_ruby.hh>
#include <paludis/environment/default/default_environment.hh>
#include <paludis/environment/default/default_config.hh>
#include <paludis/environment/no_config/no_config_environment.hh>
#include <ruby.h>

using namespace paludis;
using namespace paludis::ruby;

#define RUBY_FUNC_CAST(x) reinterpret_cast<VALUE (*)(...)>(x)

namespace
{
    static VALUE c_environment;
    static VALUE c_default_environment;
    static VALUE c_default_config;
    static VALUE c_no_config_environment;

    class EnvironmentData
    {
        private:
            Environment * _e;

        public:
            Environment * const env_ptr;

            EnvironmentData(Environment * const ee, Environment * const free_e = 0) :
                _e(free_e),
                env_ptr(ee)
            {
            }

            ~EnvironmentData()
            {
                delete _e;
            }
    };

    VALUE
    environment_query_use(int argc, VALUE * argv, VALUE self)
    {
        EnvironmentData * env_data;
        Data_Get_Struct(self, EnvironmentData, env_data);

        try
        {
            if (1 == argc || 2 == argc)
            {
                PackageDatabaseEntry * pde_ptr(0);
                if (2 == argc)
                    Data_Get_Struct(argv[1], PackageDatabaseEntry, pde_ptr);

                return env_data->env_ptr->query_use(UseFlagName(STR2CSTR(argv[0])), pde_ptr) ? Qtrue : Qfalse;
            }
            else
                rb_raise(rb_eArgError, "Environment.query_use expects one or two arguments, but got %d", argc);
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    VALUE
    environment_accept_keyword(int argc, VALUE * argv, VALUE self)
    {
        EnvironmentData * env_data;
        Data_Get_Struct(self, EnvironmentData, env_data);

        try
        {
            if (1 == argc || 2 == argc)
            {
                PackageDatabaseEntry * pde_ptr(0);
                if (2 == argc)
                    Data_Get_Struct(argv[1], PackageDatabaseEntry, pde_ptr);

                return env_data->env_ptr->accept_keyword(KeywordName(
                            STR2CSTR(argv[0])), pde_ptr) ? Qtrue : Qfalse;
            }
            else
                rb_raise(rb_eArgError, "Environment.accept_keyword expects one or two arguments, but got %d", argc);
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    VALUE
    environment_accept_license(int argc, VALUE * argv, VALUE self)
    {
        EnvironmentData * env_data;
        Data_Get_Struct(self, EnvironmentData, env_data);

        try
        {
            if (1 == argc || 2 == argc)
            {
                PackageDatabaseEntry * pde_ptr(0);
                if (2 == argc)
                    Data_Get_Struct(argv[1], PackageDatabaseEntry, pde_ptr);

                return env_data->env_ptr->accept_license(
                        std::string(STR2CSTR(argv[0])), pde_ptr) ? Qtrue : Qfalse;
            }
            else
                rb_raise(rb_eArgError, "Environment.accept_license expects one or two arguments, but got %d", argc);
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    VALUE
    environment_mask_reasons(VALUE self, VALUE pde)
    {
        EnvironmentData * env_data;
        Data_Get_Struct(self, EnvironmentData, env_data);

        PackageDatabaseEntry * pde_ptr(0);
        Data_Get_Struct(pde, PackageDatabaseEntry, pde_ptr);
        try
        {
            MaskReasons r(env_data->env_ptr->mask_reasons(*pde_ptr));
            return mask_reasons_to_value(r);
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    VALUE
    environment_package_database(VALUE self)
    {
        EnvironmentData * env_data;
        Data_Get_Struct(self, EnvironmentData, env_data);

        try
        {
            return package_database_to_value(env_data->env_ptr->package_database());
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    VALUE
    default_config_config_suffix(VALUE)
    {
        try
        {
            return rb_str_new2(DefaultConfig::config_suffix().c_str());
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    VALUE
    default_config_config_suffix_set(VALUE klass, VALUE str)
    {
        try
        {
            DefaultConfig::set_config_suffix(stringify(STR2CSTR(str)));
            return klass;
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    VALUE
    no_config_environment_init(VALUE self, VALUE)
    {
        return self;
    }

    VALUE
    no_config_environment_new(VALUE self, VALUE s)
    {
        std::string path;
        try
        {
            if (T_STRING == TYPE(s))
                path = STR2CSTR(s);
            else if (rb_obj_is_kind_of(s, rb_cDir))
                path = STR2CSTR(rb_funcall(s, rb_intern("path"), 0));
            else
                rb_raise(rb_eTypeError, "NoConfigEnvironment.new expects a string or Dir");

            NoConfigEnvironment * e(new NoConfigEnvironment(NoConfigEnvironmentParams::create()
                        .repository_dir(FSEntry(path))
                        .accept_unstable(false)));
            EnvironmentData * ptr(new EnvironmentData(e, e));
            VALUE tdata(Data_Wrap_Struct(self, 0, &Common<EnvironmentData>::free, ptr));
            rb_obj_call_init(tdata, 1, &s);
            return tdata;
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    VALUE
    default_environment_new(VALUE self)
    {
        try
        {
            EnvironmentData * ptr(new EnvironmentData(DefaultEnvironment::get_instance()));
            return Data_Wrap_Struct(self, 0, &Common<EnvironmentData>::free, ptr);
        }
        catch (const std::exception & e)
        {
            exception_to_ruby_exception(e);
        }
    }

    void do_register_environment()
    {
        rb_require("singleton");

        c_environment = rb_define_class_under(master_class(), "Environment", rb_cObject);
        rb_funcall(c_environment, rb_intern("private_class_method"), 1, rb_str_new2("new"));
        rb_define_method(c_environment, "query_use", RUBY_FUNC_CAST(&environment_query_use), -1);
        rb_define_method(c_environment, "accept_keyword", RUBY_FUNC_CAST(&environment_accept_keyword), -1);
        rb_define_method(c_environment, "accept_license", RUBY_FUNC_CAST(&environment_accept_license), -1);
        rb_define_method(c_environment, "mask_reasons", RUBY_FUNC_CAST(&environment_mask_reasons), 1);
        rb_define_method(c_environment, "package_database", RUBY_FUNC_CAST(&environment_package_database), 0);

        c_default_environment = rb_define_class_under(master_class(), "DefaultEnvironment", c_environment);
        rb_define_singleton_method(c_default_environment, "new", RUBY_FUNC_CAST(&default_environment_new), 0);
        rb_funcall(rb_const_get(rb_cObject, rb_intern("Singleton")), rb_intern("included"), 1, c_default_environment);

        c_default_config = rb_define_class_under(master_class(), "DefaultConfig", rb_cObject);
        rb_funcall(c_default_config, rb_intern("private_class_method"), 1, rb_str_new2("new"));
        rb_define_singleton_method(c_default_config, "config_suffix",
                RUBY_FUNC_CAST(&default_config_config_suffix), 0);
        rb_define_singleton_method(c_default_config, "config_suffix=",
                RUBY_FUNC_CAST(&default_config_config_suffix_set), 1);

        c_no_config_environment = rb_define_class_under(master_class(), "NoConfigEnvironment", c_environment);
        rb_define_singleton_method(c_no_config_environment, "new", RUBY_FUNC_CAST(&no_config_environment_new), 1);
        rb_define_method(c_no_config_environment, "initialize", RUBY_FUNC_CAST(&no_config_environment_init), 1);
    }
}

RegisterRubyClass::Register paludis_ruby_register_environment PALUDIS_ATTRIBUTE((used))
    (&do_register_environment);

