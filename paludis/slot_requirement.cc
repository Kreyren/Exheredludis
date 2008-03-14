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

#include <paludis/slot_requirement.hh>
#include <paludis/util/visitor-impl.hh>
#include <ostream>

using namespace paludis;

template class ConstAcceptInterface<SlotRequirementVisitorTypes>;
template class ConstAcceptInterfaceVisitsThis<SlotRequirementVisitorTypes, SlotExactRequirement>;
template class ConstAcceptInterfaceVisitsThis<SlotRequirementVisitorTypes, SlotAnyLockedRequirement>;
template class ConstAcceptInterfaceVisitsThis<SlotRequirementVisitorTypes, SlotAnyUnlockedRequirement>;

std::ostream &
paludis::operator<< (std::ostream & s, const SlotRequirement & r)
{
    s << r.as_string();
    return s;
}
