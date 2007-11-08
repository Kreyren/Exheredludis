/* vim: set sw=4 sts=4 et foldmethod=syntax : */

/*
 * Copyright (c) 2007 Ciaran McCreesh
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

#include <paludis/repositories/unpackaged/unpackaged_repository.hh>
#include <paludis/repositories/unpackaged/unpackaged_id.hh>
#include <paludis/util/sequence.hh>
#include <paludis/util/set.hh>
#include <paludis/util/private_implementation_pattern-impl.hh>
#include <paludis/util/make_shared_ptr.hh>
#include <paludis/util/stringify.hh>
#include <paludis/package_id.hh>
#include <paludis/repository_info.hh>
#include <paludis/action.hh>

using namespace paludis;
using namespace paludis::unpackaged_repositories;

#include <paludis/repositories/unpackaged/unpackaged_repository-sr.cc>

namespace paludis
{
    template <>
    struct Implementation<UnpackagedRepository>
    {
        const UnpackagedRepositoryParams params;
        tr1::shared_ptr<const PackageID> id;
        tr1::shared_ptr<PackageIDSequence> ids;
        tr1::shared_ptr<QualifiedPackageNameSet> package_names;
        tr1::shared_ptr<CategoryNamePartSet> category_names;

        Implementation(const RepositoryName & n,
                const UnpackagedRepositoryParams & p) :
            params(p),
            id(new UnpackagedID(params.environment, params.name, params.version, params.slot, n, params.location,
                        params.build_dependencies, params.run_dependencies, params.description)),
            ids(new PackageIDSequence),
            package_names(new QualifiedPackageNameSet),
            category_names(new CategoryNamePartSet)
        {
            ids->push_back(id);
            package_names->insert(id->name());
            category_names->insert(id->name().category);
        }
    };
}

UnpackagedRepository::UnpackagedRepository(const RepositoryName & n,
        const UnpackagedRepositoryParams & params) :
    PrivateImplementationPattern<UnpackagedRepository>(new Implementation<UnpackagedRepository>(n, params)),
    Repository(n, RepositoryCapabilities::create()
            .installed_interface(0)
            .sets_interface(0)
            .syncable_interface(0)
            .use_interface(0)
            .world_interface(0)
            .mirrors_interface(0)
            .environment_variable_interface(0)
            .provides_interface(0)
            .virtuals_interface(0)
            .make_virtuals_interface(0)
            .destination_interface(0)
            .e_interface(0)
            .hook_interface(0)
            .qa_interface(0)
            .manifest_interface(0),
            "unpackaged")
{
    tr1::shared_ptr<RepositoryInfoSection> config_info(new RepositoryInfoSection("Configuration information"));

    config_info->add_kv("location", stringify(_imp->params.location));
    config_info->add_kv("name", stringify(_imp->params.name));
    config_info->add_kv("version", stringify(_imp->params.version));
    config_info->add_kv("slot", stringify(_imp->params.slot));
    config_info->add_kv("format", "unpackaged");
    config_info->add_kv("build_dependencies", _imp->params.build_dependencies);
    config_info->add_kv("run_dependencies", _imp->params.run_dependencies);
    config_info->add_kv("description", _imp->params.description);

    _info->add_section(config_info);
}

UnpackagedRepository::~UnpackagedRepository()
{
}

tr1::shared_ptr<const PackageIDSequence>
UnpackagedRepository::package_ids(const QualifiedPackageName & n) const
{
    return n == _imp->id->name() ? _imp->ids : make_shared_ptr(new PackageIDSequence);
}

tr1::shared_ptr<const QualifiedPackageNameSet>
UnpackagedRepository::package_names(const CategoryNamePart & c) const
{
    return c == _imp->id->name().category ? _imp->package_names : make_shared_ptr(new QualifiedPackageNameSet);
}

tr1::shared_ptr<const CategoryNamePartSet>
UnpackagedRepository::category_names() const
{
    return _imp->category_names;
}

tr1::shared_ptr<const CategoryNamePartSet>
UnpackagedRepository::category_names_containing_package(const PackageNamePart & p) const
{
    return p == _imp->id->name().package ? _imp->category_names : make_shared_ptr(new CategoryNamePartSet);
}

bool
UnpackagedRepository::has_package_named(const QualifiedPackageName & q) const
{
    return q == _imp->id->name();
}

bool
UnpackagedRepository::has_category_named(const CategoryNamePart & c) const
{
    return c == _imp->id->name().category;
}

bool
UnpackagedRepository::some_ids_might_support_action(const SupportsActionTestBase & test) const
{
    return _imp->id->supports_action(test);
}

void
UnpackagedRepository::invalidate()
{
    _imp.reset(new Implementation<UnpackagedRepository>(name(), _imp->params));
}

void
UnpackagedRepository::invalidate_masks()
{
}

