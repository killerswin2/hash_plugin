#include "hash.hpp"
#include "commands.hpp"

static sqf_script_type game_data_hashmap_new_type;
static int calls = 0;

const sqf_script_type& game_data_hashmap_new::type() const
{
	return game_data_hashmap_new_type;
}

serialization_return game_data_hashmap_new::serialize(param_archive& ar)
{
	game_data::serialize(ar);
	size_t entryCount;
	if (ar._isExporting) entryCount;
	return serialization_return::no_error;
}

game_data* create_game_data_hashmap_new(param_archive* arch)
{
	auto data = new game_data_hashmap_new;
	if (arch)
	{
		data->serialize(*arch);
	}
	return data;
}


/**
 * @brief creates the new hashmap object
 * @return 
*/
game_value create_game_data_hashmap_object()
{
	return game_value(new game_data_hashmap_new());
}

/**
 * @brief Returns all Thermal Imaging parameters
 * @param gs
 * @return
*/
game_value getTIParameters2_hashmap_new(game_state& gs)
{
    game_data_hashmap_new* newhashmap = new game_data_hashmap_new();
    auto hashmap = intercept::sqf::get_ti_parameters();
    for (auto& iter : hashmap)
    {
        newhashmap->hashmap[iter.key] = iter.value;
    }

    return game_value(newhashmap);
}

/**
 * @brief Obtain the current system's video settings
 * @param gs
 * @return
*/
game_value getVideoOptions2_hashmap_new(game_state& gs)
{
    game_data_hashmap_new* newhashmap = new game_data_hashmap_new();
    auto hashmap = intercept::sqf::get_video_options();
    for (auto& iter : hashmap)
    {
        newhashmap->hashmap[iter.key] = iter.value;
    }

    return game_value(newhashmap);
}



/**
 * @brief set a new value in the hashmap
 * @param gs 
 * @param hashmap 
 * @param valueInfo 
 * @return 
*/
game_value set_hashmap_new(game_state& gs, game_value_parameter hashmap, game_value_parameter valueInfo)
{
    if (hashmap.is_nil())
    {
        // game_state
        gs.set_script_error(game_state::game_evaluator::evaluator_error_type::gen, r_string(""));
        return {};
    }
    else if (!gs.error_check_size( valueInfo, 2))
    {
        return {};
    }
    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());
    
    // errors handled now check types
    // and break array into componets
    bool insert = false;
    if (valueInfo.size() == 3)
    {
        insert = valueInfo[2];
    }

    auto data = valueInfo[0].data;
    if (!data) return {};
    const auto _type = valueInfo[0].type();
    if (_type == game_data_array::type_def)
    {
        game_hashmap->hashmap[valueInfo[0]] = valueInfo[1];
    }
    else if (_type == game_data_bool::type_def)
    {
        game_hashmap->hashmap[valueInfo[0]] = valueInfo[1];
    }
    else if (_type == game_data_code::type_def)
    {
        game_hashmap->hashmap[valueInfo[0]] = valueInfo[1];
    }
    else if (_type == game_data_config::type_def)
    {
        game_hashmap->hashmap[valueInfo[0]] = valueInfo[1];
    }
    else if (_type == game_data_namespace::type_def)
    {
        game_hashmap->hashmap[valueInfo[0]] = valueInfo[1];
    }
    else if (_type == game_data_number::type_def)
    {
        game_hashmap->hashmap[valueInfo[0]] = valueInfo[1];
    }
    else if (_type == game_data_side::type_def)
    {
        game_hashmap->hashmap[valueInfo[0]] = valueInfo[1];
    }
    else if (_type == game_data_string::type_def)
    {
        game_hashmap->hashmap[valueInfo[0]] = valueInfo[1];
    }
    return {};
}

/**
 * @brief counts the elements in a hashmap
 * @param gs 
 * @param hashmap 
 * @return 
*/
game_value count_hashmap_new(game_state& gs, game_value_parameter hashmap)
{
    if (hashmap.is_nil())
    {
        // game_state
        gs.set_script_error(game_state::game_evaluator::evaluator_error_type::gen, r_string(""));
        return {};
    }
    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());

    return static_cast<float>(game_hashmap->hashmap.size());
}

/**
 * @brief creates a hashmap from an array of key, value pairs
 * @param gs 
 * @param array 
 * @return 
*/
game_value create_from_array_hashmap_new(game_state& gs, game_value_parameter array)
{
    if (array.is_nil())
    {
        return {};
    }
    else if (array.type() != game_data_array::type_def)
    {
        return {};
    }
    game_data_hashmap_new* game_hashmap = new game_data_hashmap_new();
    auto_array<game_value> keyValues = array.to_array();
    for (int i = 0; i < keyValues.size(); i++)
    {
        game_value key = keyValues[i][0];
        game_value value = keyValues[i][1];
        auto data = key.data;
        if (!data) return {};
        const auto _type = key.type();
        if (_type == game_data_array::type_def)
        {
            game_hashmap->hashmap[key] = value;
        }
        else if (_type == game_data_bool::type_def)
        {
            game_hashmap->hashmap[key] = value;
        }
        else if (_type == game_data_code::type_def)
        {
            game_hashmap->hashmap[key] = value;
        }
        else if (_type == game_data_config::type_def)
        {
            game_hashmap->hashmap[key] = value;
        }
        else if (_type == game_data_namespace::type_def)
        {
            game_hashmap->hashmap[key] = value;
        }
        else if (_type == game_data_number::type_def)
        {
            game_hashmap->hashmap[key] = value;
        }
        else if (_type == game_data_side::type_def)
        {
            game_hashmap->hashmap[key] = value;
        }
        else if (_type == game_data_string::type_def)
        {
            game_hashmap->hashmap[key] = value;
        }
    }
    return game_value(game_hashmap);
}

/**
 * @brief gets all the keys from the hashmap
 * @param gs 
 * @param hashmap 
 * @return 
*/
game_value keys_hashmap_new(game_state& gs, game_value_parameter hashmap)
{
    if (hashmap.is_nil())
    {
        return {};
    }
    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());
    auto_array<game_value> keys;
    // reserve the size so that the hash map placement is faster
    keys.reserve(game_hashmap->hashmap.size());

    for (auto iter : game_hashmap->hashmap)
    {
        keys.push_back(iter.first);
    }
    return game_value(keys);
}

/**
 * @brief convert the hashmap to a array representation
 * @param gs 
 * @param hashmap 
 * @return 
*/
game_value toarray_hashmap_new(game_state& gs, game_value_parameter hashmap)
{
    if (hashmap.is_nil())
    {
        return {};
    }
    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());

    auto_array<game_value> arrayKeys;
    auto_array<game_value> arrayValues;
    arrayKeys.reserve(game_hashmap->hashmap.size());
    arrayValues.reserve(game_hashmap->hashmap.size());

    for (auto& [key, value] : game_hashmap->hashmap)
    {
        arrayKeys.push_back(key);
        arrayValues.push_back(value);

    }
    auto_array<game_value> array {game_value(arrayKeys), game_value(arrayValues)};
    return game_value(array);
}

/**
 * @brief returns unique items form a unit
 * @param gs 
 * @param unit 
 * @return 
*/
game_value uniqueUnitItems_hashmap_new(game_state& gs, game_value_parameter unit)
{
    if (unit.is_nil())
    {
        return {};
    }
    game_data_hashmap_new* newhashmap = new game_data_hashmap_new();
    auto hashmap = intercept::sqf::unique_unit_items(unit);
    for (auto& iter : hashmap)
    {
        newhashmap->hashmap[iter.key] = iter.value;
    }

    return game_value(newhashmap);
}

/**
 * @brief returns all the values in the hashmap
 * @param gs 
 * @param hashmap 
 * @return 
*/
game_value values_hashmap_new(game_state& gs, game_value_parameter hashmap)
{
    if (hashmap.is_nil())
    {
        return{};
    }
    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());
    auto_array<game_value> values;
    // reserve this size, so that push_back does allocate memory all the time.
    values.reserve(game_hashmap->hashmap.size());

    for (auto iter : game_hashmap->hashmap)
    {
        values.push_back(iter.second);
    }

    return game_value(values);
}

/**
 * @brief creates hashmap from supplied keys and values.
 * @param keys
 * @param values
 * @return hashmap
*/
game_value create_from_array_hashmap_new2(game_state& gs, game_value_parameter keys, game_value_parameter values)
{
    game_data_hashmap_new* game_hashmap = new game_data_hashmap_new();

    auto_array<game_value>& arrayKeys = keys.to_array();
    auto_array<game_value>& arrayValues = values.to_array();
    for (int i = 0; i < arrayKeys.size(); i++)
    {
        auto _type = arrayKeys[i].type();
        if (_type == game_data_array::type_def || _type == game_data_bool::type_def || _type == game_data_code::type_def || _type == game_data_config::type_def ||
            _type == game_data_namespace::type_def || _type == game_data_number::type_def || _type == game_data_side::type_def || _type == game_data_string::type_def)
        {
            game_value value;
            if (arrayValues.size() > i)
            {
                value = arrayValues[i];
            }
            game_hashmap->hashmap[arrayKeys[i]] = value;
        }
    }

    return game_value(game_hashmap);
}

/**
 * @brief deletes an element in the hashmap by key
 * @param gs 
 * @param hashmap 
 * @param key 
 * @return 
*/
game_value delete_at_hashmap_new(game_state& gs, game_value_parameter hashmap, game_value_parameter key)
{
    if (hashmap.is_nil())
    {
        return {};
    }

    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());
    auto data = key.data;
    if (!data) return {};
    const auto _type = key.type();
    if (_type == game_data_array::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        game_value returnObject = iter.kv_->second;
        game_hashmap->hashmap.erase(key);
        return returnObject;
    }
    else if (_type == game_data_bool::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        game_value returnObject = iter.kv_->second;
        game_hashmap->hashmap.erase(key);
        return returnObject;
    }
    else if (_type == game_data_code::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        game_value returnObject = iter.kv_->second;
        game_hashmap->hashmap.erase(key);
        return returnObject;
    }
    else if (_type == game_data_config::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        game_value returnObject = iter.kv_->second;
        game_hashmap->hashmap.erase(key);
        return returnObject;
    }
    else if (_type == game_data_namespace::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        game_value returnObject = iter.kv_->second;
        game_hashmap->hashmap.erase(key);
        return returnObject;
    }
    else if (_type == game_data_number::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        game_value returnObject = iter.kv_->second;
        game_hashmap->hashmap.erase(key);
        return returnObject;
    }
    else if (_type == game_data_side::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        game_value returnObject = iter.kv_->second;
        game_hashmap->hashmap.erase(key);
        return returnObject;
    }
    else if (_type == game_data_string::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        game_value returnObject = iter.kv_->second;
        game_hashmap->hashmap.erase(key);
        return returnObject;
    }
    return {};

}

/**
 * @brief gets the data from the hashmap
 * @param gs
 * @param hashmap
 * @param key
 * @return
*/
game_value get_hashmap_new(game_state& gs, game_value_parameter hashmap, game_value_parameter key)
{
    if (hashmap.is_nil())
    {
        // game_state
        gs.set_script_error(game_state::game_evaluator::evaluator_error_type::gen, r_string(""));
        return {};
    }
    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());

    auto data = key.data;
    if (!data) return {};
    const auto _type = key.type();
    if (_type == game_data_array::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_bool::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_code::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_config::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_namespace::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_number::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_side::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_string::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return {};
        }
        return iter.kv_->second;
    }
    return {};
}

/**
 * @brief gets the data from the hashmap, if it does exist, the default is returned.
 * @param gs
 * @param hashmap
 * @param key
 * @return
*/
game_value get_or_default_hashmap_new(game_state& gs, game_value_parameter hashmap, game_value_parameter array)
{
    if (hashmap.is_nil())
    {
        // game_state
        gs.set_script_error(game_state::game_evaluator::evaluator_error_type::gen, r_string(""));
        return {};
    }
    else if (array.size() < 2)
    {
        return {};
    }

    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());
    auto key = array[0];
    auto data = key.data;
    if (!data) return {};
    const auto _type = key.type();
    if (_type == game_data_array::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return array[1];
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_bool::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return array[1];
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_code::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return array[1];
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_config::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return array[1];
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_namespace::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return array[1];
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_number::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return array[1];
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_side::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return array[1];
        }
        return iter.kv_->second;
    }
    else if (_type == game_data_string::type_def)
    {
        auto iter = game_hashmap->hashmap.find(key);
        if (iter == game_hashmap->hashmap.end())
        {
            return array[1];
        }
        return iter.kv_->second;
    }
    return array[1];
}


/**
 * @brief returns true or false if key is in hashmap
 * @param gs
 * @param hashmap
 * @param key
 * @return
*/
game_value in_hashmap_new(game_state& gs, game_value_parameter key, game_value_parameter hashmap)
{
    if (hashmap.is_nil())
    {
        // game_state
        gs.set_script_error(game_state::game_evaluator::evaluator_error_type::gen, r_string(""));
        return {};
    }

    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());
    auto data = key.data;
    if (!data) return {};
    const auto _type = key.type();
    if (_type == game_data_array::type_def || _type == game_data_bool::type_def || _type == game_data_code::type_def || _type == game_data_config::type_def || 
        _type == game_data_namespace::type_def || _type == game_data_number::type_def || _type == game_data_side::type_def || _type == game_data_string::type_def)
    {
        for (auto& iter : game_hashmap->hashmap)
        {
            if (iter.first == key)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}

/**
 * @brief inserts elements into the hashmap
 * @param gs
 * @param hashmap
 * @param key
 * @return
*/
game_value insert_hashmap_new(game_state& gs, game_value_parameter hashmap, game_value_parameter array)
{
    if (hashmap.is_nil())
    {
        // game_state
        gs.set_script_error(game_state::game_evaluator::evaluator_error_type::gen, r_string(""));
        return {};
    }

    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());
    
    // two conditions, element 0 is a boolean
    // 0 element is an array 

    if (array.size() < 0)
    {
        return {};
    }

    if (array[0].type() == game_data_bool::type_def)
    {
        bool splitArrays = reinterpret_cast<game_data_bool*>(array[0].data.get())->val;
        if (splitArrays)
        {
            if (array[1].size() != 2)
            {
                return {};
            }
            auto_array<game_value>& arrayKeys = array[1][0].to_array();
            auto_array<game_value>& arrayValues = array[1][1].to_array();
            for (int i = 0; i < arrayKeys.size(); i++)
            {
                auto _type = arrayKeys[i].type();
                if (_type == game_data_array::type_def || _type == game_data_bool::type_def || _type == game_data_code::type_def || _type == game_data_config::type_def ||
                    _type == game_data_namespace::type_def || _type == game_data_number::type_def || _type == game_data_side::type_def || _type == game_data_string::type_def)
                {
                    game_value value;
                    if (arrayValues.size() > i)
                    {
                        value = arrayValues[i];
                    }
                    game_hashmap->hashmap[arrayKeys[i]] = value;
                }
            }
        }
        else
        {
            if (array[1].type() != game_data_array::type_def)
            {
                return{};
            }
            auto_array<game_value> keyValues = array[1].to_array();
            for (int i = 0; i < keyValues.size(); i++)
            {
                game_value key = keyValues[i][0];
                game_value value = keyValues[i][1];
                auto data = key.data;
                if (!data) return {};
                const auto _type = key.type();
                if (_type == game_data_array::type_def)
                {
                    game_hashmap->hashmap[key] = value;
                }
                else if (_type == game_data_bool::type_def)
                {
                    game_hashmap->hashmap[key] = value;
                }
                else if (_type == game_data_code::type_def)
                {
                    game_hashmap->hashmap[key] = value;
                }
                else if (_type == game_data_config::type_def)
                {
                    game_hashmap->hashmap[key] = value;
                }
                else if (_type == game_data_namespace::type_def)
                {
                    game_hashmap->hashmap[key] = value;
                }
                else if (_type == game_data_number::type_def)
                {
                    game_hashmap->hashmap[key] = value;
                }
                else if (_type == game_data_side::type_def)
                {
                    game_hashmap->hashmap[key] = value;
                }
                else if (_type == game_data_string::type_def)
                {
                    game_hashmap->hashmap[key] = value;
                }
            }
        }
    }
    else if (array[0].type() == game_data_array::type_def)
    {
        auto_array<game_value> keyValues = array.to_array();
        for (int i = 0; i < keyValues.size(); i++)
        {
            game_value key = keyValues[i][0];
            game_value value = keyValues[i][1];
            auto data = key.data;
            if (!data) return {};
            const auto _type = key.type();
            if (_type == game_data_array::type_def)
            {
                game_hashmap->hashmap[key] = value;
            }
            else if (_type == game_data_bool::type_def)
            {
                game_hashmap->hashmap[key] = value;
            }
            else if (_type == game_data_code::type_def)
            {
                game_hashmap->hashmap[key] = value;
            }
            else if (_type == game_data_config::type_def)
            {
                game_hashmap->hashmap[key] = value;
            }
            else if (_type == game_data_namespace::type_def)
            {
                game_hashmap->hashmap[key] = value;
            }
            else if (_type == game_data_number::type_def)
            {
                game_hashmap->hashmap[key] = value;
            }
            else if (_type == game_data_side::type_def)
            {
                game_hashmap->hashmap[key] = value;
            }
            else if (_type == game_data_string::type_def)
            {
                game_hashmap->hashmap[key] = value;
            }
        }
    }
    return {};
}

/**
 * @brief all key value pairs in hashmap2, will be added to modHashmap. If a key exist in modHashmap, hashmap2 will not overwrite the value
 * @param gs 
 * @param modHashmap 
 * @param hashmap2
 * @return 
*/
game_value merge_hashmap_new(game_state& gs, game_value_parameter modHashmap, game_value_parameter hashmap2)
{
    if (modHashmap.is_nil())
    {
        return {};
    }
    else if (hashmap2.is_nil())
    {
        return {};
    }

    game_data_hashmap_new* modifiedHashmap = reinterpret_cast<game_data_hashmap_new*>(modHashmap.data.get());
    game_data_hashmap_new* modifierHashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap2.data.get());

    for (auto rit = modifierHashmap->hashmap.begin(); rit != modifierHashmap->hashmap.end(); )
    {
        auto fit = modifiedHashmap->hashmap.find(rit->first);
        if (fit == modifiedHashmap->hashmap.end())
        {
            modifiedHashmap->hashmap.insert_unique(rit->first, rit->second);
        }
        else
        {
            ++rit;
        }
    }
    return {};
}

/**
 * @brief merge hashmaps. modHashmap will be modified. If key exists in modHashmap, it will be overwritten by the value in hashmap2 if bool set to true
 * @param gs 
 * @param modHashmap 
 * @param array 
 * @return 
*/
game_value merge_hashmap_new2(game_state& gs, game_value_parameter modHashmap, game_value_parameter array)
{
    if (modHashmap.is_nil())
    {
        return {};
    }
    else if (array.is_nil())
    {
        return {};
    }

    if (array.size() != 2)
    {
        return {};
    }

    game_data_hashmap_new* modifiedHashmap = reinterpret_cast<game_data_hashmap_new*>(modHashmap.data.get());
    game_data_hashmap_new* modifierHashmap = reinterpret_cast<game_data_hashmap_new*>(array[0].data.get());
    bool doOverWrites = reinterpret_cast<game_data_bool*>(array[1].data.get())->val;

    if (doOverWrites)
    {
        for (auto& [key, value] : modifierHashmap->hashmap)
        {
            modifiedHashmap->hashmap[key] = value;
        }

    } 
    else
    {
        for (auto rit = modifierHashmap->hashmap.begin(); rit != modifierHashmap->hashmap.end(); )
        {
            auto fit = modifiedHashmap->hashmap.find(rit->first);
            if (fit == modifiedHashmap->hashmap.end())
            {
                modifiedHashmap->hashmap.insert_unique(rit->first, rit->second);
            }
            else
            {
                ++rit;
            }
        }
    }
    
    return {};
}

/**
 * @brief converts hashmap to an array of key values, if splitArray is true then form is key array, value array
 * @param gs 
 * @param hashmap 
 * @param splitArrays 
 * @return 
*/
game_value to_array_hashmap_new2(game_state& gs, game_value_parameter hashmap, game_value_parameter splitArrays)
{
    if (hashmap.is_nil())
    {
        return {};
    }
    else if (splitArrays.is_nil())
    {
        return {};
    }

    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());

    // you idiot Ellis, get the val here, don't trunicate the pointer
    bool doSplitArrays = reinterpret_cast<game_data_bool*>(splitArrays.data.get())->val;
    if (doSplitArrays)
    {
        return toarray_hashmap_new(gs, hashmap);
    }
    else
    {
        auto_array<game_value> array;
        array.reserve(game_hashmap->hashmap.size());
        for (auto iter : game_hashmap->hashmap)
        {
            auto_array<game_value> nestedArray = { iter.first, iter.second };
            array.push_back(game_value(nestedArray));
        }
        return game_value(array);
    }

    return {};
}

/**
 * @brief foreach on the hashmap. No idea if this works.
 * @param gs 
 * @param code 
 * @param hashmap 
 * @return 
*/
game_value for_each_hashmap_new(game_state& gs, game_value_parameter code, game_value_parameter hashmap)
{
    if (code.is_nil())
    {
        return {};
    }
    else if (hashmap.is_nil())
    {
        return {};
    }

    game_data_code* realCode = reinterpret_cast<game_data_code*>(code.data.get());
    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());

    vm_context* context = gs.get_vm_context();

    int topItem = context->scriptStack.size()-1;
    vm_context::callstack_item* item = nullptr;
    game_var_space varibles;
    if (topItem > 0)
    {
        varibles = context->callstack[topItem].get()->_varSpace;
        item = context->callstack[topItem].get();
    }
    vm_context::callstack_item *stackItem = new CallStackItemHashmapNewForEach(game_hashmap, realCode, item, varibles, topItem-1, &gs);
    context->add_callstack_item(stackItem);

    return {};
}

/**
 * @brief apply on hashmap
 * @param gs
 * @param code
 * @param hashmap
 * @return
*/
game_value apply_hashmap_new(game_state& gs, game_value_parameter hashmap, game_value_parameter code)
{
    if (code.is_nil())
    {
        return {};
    }
    else if (hashmap.is_nil())
    {
        return {};
    }

    game_data_code* realCode = reinterpret_cast<game_data_code*>(code.data.get());
    game_data_hashmap_new* game_hashmap = reinterpret_cast<game_data_hashmap_new*>(hashmap.data.get());

    vm_context* context = gs.get_vm_context();

    int topItem = context->scriptStack.size() - 1;
    vm_context::callstack_item* item = nullptr;
    game_var_space varibles;
    if (topItem > 0)
    {
        varibles = context->callstack[topItem].get()->_varSpace;
        item = context->callstack[topItem].get();
    }
    vm_context::callstack_item* stackItem = new CallStackItemHashmapNewApply(game_hashmap, realCode, item, varibles, topItem - 1, &gs);
    context->add_callstack_item(stackItem);

    return {};
}

void pre_start_hashing()
{
    auto codeType = intercept::client::host::register_sqf_type("HASHMAP"sv, "Hashmap"sv, "Hashmap, associative array", "Hashmap"sv, create_game_data_hashmap_new);
    game_data_hashmap_new_type = *codeType.second;

    Commands& commands = Commands::get();
    //nular
    commands.addCommand("createHashMap2", "", userFunctionWrapper<create_game_data_hashmap_object>, codeType.first);
    commands.addCommand("getTIParameters2", "", getTIParameters2_hashmap_new, codeType.first);
    commands.addCommand("getVideoOptions2", "", getVideoOptions2_hashmap_new, codeType.first);

    // unary
    commands.addCommand("count2", "", count_hashmap_new, game_data_type::SCALAR, codeType.first);
    commands.addCommand("createHashMapFromArray2", "", create_from_array_hashmap_new, codeType.first, game_data_type::ARRAY);
    commands.addCommand("keys2", "",keys_hashmap_new, game_data_type::ARRAY ,codeType.first);
    commands.addCommand("toArray2", "", toarray_hashmap_new, game_data_type::ARRAY, codeType.first);
    commands.addCommand("uniqueUnitItems2", "", uniqueUnitItems_hashmap_new, codeType.first, game_data_type::OBJECT);
    commands.addCommand("values2", "", values_hashmap_new, game_data_type::ARRAY, codeType.first);

    // binary
    commands.addCommand("apply2", "", apply_hashmap_new, game_data_type::ARRAY, codeType.first, game_data_type::CODE);
    commands.addCommand("createHashMapFromArray2", "", create_from_array_hashmap_new2, codeType.first, game_data_type::ARRAY, game_data_type::ARRAY);
    commands.addCommand("deleteAt2", "", delete_at_hashmap_new, game_data_type::ANY, codeType.first, game_data_type::ANY);
    commands.addCommand("get2", "", get_hashmap_new, game_data_type::ANY, codeType.first, game_data_type::ANY);
    commands.addCommand("getOrDefault2", "", get_or_default_hashmap_new, game_data_type::ANY, codeType.first, game_data_type::ARRAY);
    commands.addCommand("in2", "", in_hashmap_new, game_data_type::BOOL, game_data_type::ANY, codeType.first);
    commands.addCommand("insert2", "", insert_hashmap_new, game_data_type::NOTHING, codeType.first, game_data_type::ARRAY);
    commands.addCommand("merge2", "", merge_hashmap_new, game_data_type::NOTHING, codeType.first, codeType.first);
    commands.addCommand("merge2", "", merge_hashmap_new2, game_data_type::NOTHING, codeType.first, game_data_type::ARRAY);
    commands.addCommand("set2", "", set_hashmap_new, game_data_type::NOTHING, codeType.first, game_data_type::ARRAY);
    commands.addCommand("toArray2", "", to_array_hashmap_new2, game_data_type::ARRAY, codeType.first, game_data_type::BOOL);
    commands.addCommand("forEach2", "", for_each_hashmap_new, game_data_type::ANY, game_data_type::CODE, codeType.first);
}

CallStackItemHashmapNewForEach::CallStackItemHashmapNewForEach(game_data_hashmap_new* hashmap, game_data_code* code, vm_context::callstack_item* parent, game_var_space varSpace, int stackPos, game_state* gs)
{
    _hashmap = hashmap;
    _code = code;
    _parent = parent;
    _varSpace = varSpace;
    _index = 0;
    _stackEndAtStart = stackPos;
    _iter = hashmap->hashmap.begin();

    // add to scope
    _stackEnd = stackPos + 1;
    _exitOrBreak = false;

}

game_instruction* CallStackItemHashmapNewForEach::next(int& d1, const game_state* s)
{
    if (_exitOrBreak)
    {
        d1 = execution::done;
        return nullptr;
    }

    const emhash8::HashMap<game_value, game_value> &hashmap = _hashmap.get()->hashmap;

    vm_context* context = s->get_vm_context();
    if (!context)
    {
        return nullptr;
    }

    // done if _index is bigger than the size of the hashmap or the iter is at end
    if (_index >= hashmap.size() || _iter == hashmap.end())
    {
        d1 = execution::done;
        return nullptr;
    }

    // verify stack size and check the fence post. Leave a nothing value on stack for value return?
    if (context->scriptStack.size() == _stackEndAtStart)
    {
        context->scriptStack.push_back(game_value());
    }
    //else if (context->scriptStack.size() != _stackEndAtStart + 1)
    //{
    //    d1 = execution::done;
    //    return nullptr;
    //}

    // actually for each stuff!!!
    // varibles in call stack here
    int topItem = context->callstack.size() - 1;
    ref<vm_context::callstack_item> item = nullptr;
    game_var_space varibles;
    if (topItem > 0)
    {
        varibles = context->callstack[topItem].get()->_varSpace;
        item = context->callstack[topItem];
    }
    
    vm_context::callstack_item* stackItem = new CallStackItemData(_code, item, varibles, context->scriptStack.size() - 1, s);
    context->add_callstack_item(stackItem);
    game_variable var = stackItem->_varSpace.variables.get("_x");
    game_variable var2 = stackItem->_varSpace.variables.get("_y");
    game_variable var3 = stackItem->_varSpace.variables.get("_foreachindex");
    
    if (stackItem->_varSpace.variables.is_null(var))
    {
        game_variable newvarible("_x"sv, game_value());
        varibles.variables.insert(newvarible);
    }

    if (stackItem->_varSpace.variables.is_null(var2))
    {
        game_variable newvarible("_y"sv, game_value());
        varibles.variables.insert(newvarible);
    }

    if (stackItem->_varSpace.variables.is_null(var3))
    {
        game_variable newvarible("_foreachindex"sv, game_value());
        varibles.variables.insert(newvarible);
    }
    stackItem->_varSpace.set_variable("_x"sv, _iter.kv_->first);
    stackItem->_varSpace.set_variable("_y"sv, _iter.kv_->second);
    stackItem->_varSpace.set_variable("_foreachindex"sv, game_value((float)_index));

    _index++;
    _iter++;

    d1 = execution::continueEx2;
    return nullptr;

}

bool CallStackItemHashmapNewForEach::someEH(void* state)
{
    return false;
}

bool CallStackItemHashmapNewForEach::someEH2(void* state)
{
    return false;
}

r_string CallStackItemHashmapNewForEach::get_type() const
{
    return r_string();
}

serialization_return CallStackItemHashmapNewForEach::serialize(param_archive& ar)
{
    return serialization_return();
}

void CallStackItemHashmapNewForEach::on_before_exec()
{
}

CallStackItemData::CallStackItemData(game_data_code* code, vm_context::callstack_item* parent, game_var_space varSpace, int stackPos,const game_state* gs)
{
    _code = code;
    _parent = parent;
    _varSpace = varSpace;
    _stackEndAtStart = stackPos;

    // add to scope
    _stackEnd = stackPos + 1;
    _programCounter = 0;
}

game_instruction* CallStackItemData::next(int& d1, const game_state* s)
{
    const auto_array<ref<game_instruction>> &codes = _code.get()->instructions;
    if (_programCounter >= codes.size())
    {
        d1 = execution::done;
        return nullptr;
    }
    else
    {
        d1 = execution::continueEx;
        return codes[_programCounter++];
    }
}

bool CallStackItemData::someEH(void* state)
{
    return false;
}

bool CallStackItemData::someEH2(void* state)
{
    return false;
}
serialization_return CallStackItemData::serialize(param_archive& ar)
{
    return serialization_return();
}

void CallStackItemData::on_before_exec()
{
}

CallStackItemHashmapNewApply::CallStackItemHashmapNewApply(game_data_hashmap_new* hashmap, game_data_code* code, vm_context::callstack_item* parent, game_var_space varSpace, int stackPos, game_state* gs)
{
    _hashmap = hashmap;
    _code = code;
    _parent = parent;
    _varSpace = varSpace;
    _stackEndAtStart = stackPos;
    _iter = hashmap->hashmap.begin();
    _index = 0;
    _array.reserve(_hashmap->hashmap.size());

    // add to scope
    _stackEnd = stackPos + 1;
    _exitOrBreak = false;
}

game_instruction* CallStackItemHashmapNewApply::next(int& d1, const game_state* s)
{
    if (_exitOrBreak)
    {
        d1 = execution::done;
        return nullptr;
    }
    calls++;

    const emhash8::HashMap<game_value, game_value>& hashmap = _hashmap.get()->hashmap;

    vm_context* context = s->get_vm_context();
    if (!context)
    {
        return nullptr;
    }

    int stackIndex = context->scriptStack.size() - 1;

    // the first one is a null value somehow, probably basic the apply function, adds it to the stack. 
    if (stackIndex == _stackEndAtStart)
    {
        if (_index != 0)
        {
            game_value stack_value = context->scriptStack[stackIndex];
            //intercept::sqf::system_chat(stack_value);
            _array.push_back(stack_value);
        }
    }
    else if (stackIndex + 1 != _stackEndAtStart)
    {
        d1 = execution::done;
        return nullptr;
    }

    // done if the iter is at end
    if (_index >= hashmap.size())
    {
        // okay that fixed it, returns most be zeroed out in the stack. Makes sense, only one return
        context->scriptStack.resize(stackIndex);
        context->scriptStack.push_back(game_value(_array));
        d1 = execution::done;
        return nullptr;
    }    

    // actually for each stuff!!!
    // varibles in call stack here
    int topItem = context->callstack.size() - 1;
    ref<vm_context::callstack_item> item = nullptr;
    game_var_space varibles;
    if (topItem > 0)
    {
        varibles = context->callstack[topItem].get()->_varSpace;
        item = context->callstack[topItem];
    }

    vm_context::callstack_item* stackItem = new CallStackItemData(_code, item, varibles, context->scriptStack.size() - 1, s);
    context->add_callstack_item(stackItem);
    game_variable var = stackItem->_varSpace.variables.get("_x");
    game_variable var2 = stackItem->_varSpace.variables.get("_y");

    if (stackItem->_varSpace.variables.is_null(var))
    {
        game_variable newvarible("_x"sv, game_value());
        varibles.variables.insert(newvarible);
    }

    if (stackItem->_varSpace.variables.is_null(var2))
    {
        game_variable newvarible("_y"sv, game_value());
        varibles.variables.insert(newvarible);
    }

    stackItem->_varSpace.set_variable("_x"sv, _iter.kv_->first);
    stackItem->_varSpace.set_variable("_y"sv, _iter.kv_->second);

    _index++;
    _iter++;

    d1 = execution::continueEx2;
    return nullptr;
}

bool CallStackItemHashmapNewApply::someEH(void* state)
{
    return false;
}

bool CallStackItemHashmapNewApply::someEH2(void* state)
{
    return false;
}

r_string CallStackItemHashmapNewApply::get_type() const
{
    return r_string();
}

serialization_return CallStackItemHashmapNewApply::serialize(param_archive& ar)
{
    return serialization_return();
}

void CallStackItemHashmapNewApply::on_before_exec()
{
}
