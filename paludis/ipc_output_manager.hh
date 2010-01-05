/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2010 Ciaran McCreesh
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

#ifndef PALUDIS_GUARD_PALUDIS_IPC_OUTPUT_MANAGER_HH
#define PALUDIS_GUARD_PALUDIS_IPC_OUTPUT_MANAGER_HH 1

#include <paludis/ipc_output_manager-fwd.hh>
#include <paludis/util/attributes.hh>
#include <paludis/util/private_implementation_pattern.hh>
#include <paludis/output_manager.hh>
#include <paludis/environment-fwd.hh>
#include <paludis/create_output_manager_info-fwd.hh>
#include <paludis/package_id-fwd.hh>
#include <paludis/action-fwd.hh>
#include <tr1/memory>
#include <tr1/functional>
#include <string>

namespace paludis
{
    class PALUDIS_VISIBLE IPCOutputManager :
        private PrivateImplementationPattern<IPCOutputManager>,
        public OutputManager
    {
        public:
            IPCOutputManager(
                    const int pipe_read_fd,
                    const int pipe_write_fd,
                    const CreateOutputManagerInfo &);
            ~IPCOutputManager();

            virtual std::ostream & stdout_stream() PALUDIS_ATTRIBUTE((warn_unused_result));
            virtual std::ostream & stderr_stream() PALUDIS_ATTRIBUTE((warn_unused_result));

            virtual void succeeded();
            virtual void flush();
            virtual bool want_to_flush() const;
            virtual void nothing_more_to_come();
            virtual void message(const MessageType, const std::string &);
    };

    class PALUDIS_VISIBLE IPCInputManager :
        private PrivateImplementationPattern<IPCInputManager>
    {
        private:
            std::string _pipe_command_handler(const std::string &);
            void _copy_thread();

        public:
            IPCInputManager(
                    const Environment * const,
                    const OutputExclusivity);

            ~IPCInputManager();

            const std::tr1::function<std::string (const std::string &)> pipe_command_handler()
                PALUDIS_ATTRIBUTE((warn_unused_result));
    };

    class PALUDIS_VISIBLE OutputManagerFromIPC :
        private PrivateImplementationPattern<OutputManagerFromIPC>
    {
        public:
            OutputManagerFromIPC(
                    const Environment * const,
                    const std::tr1::shared_ptr<const PackageID> &,
                    const OutputExclusivity
                    );

            ~OutputManagerFromIPC();

            const std::tr1::shared_ptr<OutputManager> operator() (const Action &);

            const std::tr1::shared_ptr<OutputManager> output_manager_if_constructed();

            void construct_standard_if_unconstructed();
    };

#ifdef PALUDIS_HAVE_EXTERN_TEMPLATE
    extern template class PrivateImplementationPattern<IPCOutputManager>;
    extern template class PrivateImplementationPattern<IPCInputManager>;
    extern template class PrivateImplementationPattern<OutputManagerFromIPC>;
#endif

}

#endif
