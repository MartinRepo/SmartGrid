#include "../../include/server/api_handler.h"

json::value RunAlgorithms(json::value input) {
    if (input.has_field(U("selectedValues")) && input[U("selectedValues")].is_array()) {
        auto values = input[U("selectedValues")].as_array();

        vector<utility::string_t> datasets;
        for (auto& value : values) {
            if (value.is_string()) {
                datasets.push_back(value.as_string());
            }
        }

        // Total Power Cost

        // Peak Power Cost

        // Running Time

        // 假设执行完毕后，我们返回一个简单的JSON对象作为示例
        json::value result = json::value::object();
        result[U("result")] = json::value::string(U("算法执行完成"));
        return result;
    } else {
        // 如果输入JSON不符合预期格式，返回一个错误信息
        json::value error = json::value::object();
        error[U("error")] = json::value::string(U("输入格式错误或缺少'selectedValues'键"));
        return error;
    }
}