/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2008 Ciaran McCreesh
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

#ifndef PALUDIS_GUARD_PALUDIS_UTIL_KEYS_HH
#define PALUDIS_GUARD_PALUDIS_UTIL_KEYS_HH 1

#include <paludis/util/kc-fwd.hh>

namespace paludis
{
    namespace k
    {
        typedef kc::Key<1> fetch_unneeded;
        typedef kc::Key<2> safe_resume;
        typedef kc::Key<3> no_config_protect;
        typedef kc::Key<4> debug_build;
        typedef kc::Key<5> checks;
        typedef kc::Key<6> destination;
        typedef kc::Key<7> visible;
        typedef kc::Key<8> target_file;
        typedef kc::Key<9> requires_manual_fetching;
        typedef kc::Key<10> failed_automatic_fetching;
        typedef kc::Key<11> failed_integrity_checks;
    }
}

#endif
