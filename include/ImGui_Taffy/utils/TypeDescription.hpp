#pragma once

namespace ImGui_Taffy {

struct TypeDescription
{
    const char* type_name = nullptr;

    using type_description_fn_t = void (*) ();
    const type_description_fn_t type_description_fn = nullptr;

    bool type_description_interactive = false;

    // -------------------------------------------------------------------------

    constexpr TypeDescription(
        const char* type_name_,

        const type_description_fn_t type_description_fn_,
        bool type_description_interactive_
    )
        : type_name(type_name_)
        , type_description_fn(type_description_fn_)
        , type_description_interactive(type_description_interactive_)
    {}

    static constexpr TypeDescription Default()
    {
        return TypeDescription{
            nullptr,
            nullptr,
            false
        };
    }
    
    static constexpr TypeDescription NameOnly(const char* type_name)
    {
        return TypeDescription{
            type_name,
            nullptr, 
            false
        };
    }

    // -------------------------------------------------------------------------

    constexpr bool is_default() const
    {
        return 
            (type_name == nullptr) &&
            (type_description_fn == nullptr);
    }
};

constexpr TypeDescription description_or_default(
    const TypeDescription& new_description,
    const TypeDescription& default_description)
{
    return TypeDescription
    {
        new_description.type_name != nullptr ?
            new_description.type_name
        :
            default_description.type_name
        ,
        new_description.type_description_fn != nullptr ?
            new_description.type_description_fn
        :
            default_description.type_description_fn
        ,
        new_description.type_description_fn != nullptr ?
            new_description.type_description_interactive
        :
            default_description.type_description_interactive
    };
}

} // namsepace ImGui_Taffy
