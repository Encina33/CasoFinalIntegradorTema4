#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp> // Biblioteca JSON moderna

using json = nlohmann::json;

// Definición del tipo de entorno (puede extenderse según sea necesario)
struct Entorno {
    std::map<std::string, class Variant> variables;
};

// Tipos soportados por Variant
enum variant_type { Symbol, Number, List, Proc, Lambda, Cadena };

class Variant {
public:
    typedef Variant(*proc_type)(const std::vector<Variant>&);

    // Miembros de datos
    variant_type type;
    std::string val;  // Para Symbol o Cadena
    double num;       // Para Number
    std::vector<Variant> list; // Para List
    proc_type proc;    // Para Proc
    Entorno* env;      // Referencia al entorno para Lambda o Proc

    // Constructores
    Variant(variant_type type = Symbol) : type(type), num(0), env(nullptr), proc(nullptr) {}
    Variant(variant_type type, const std::string& val) : type(type), val(val), num(0), env(nullptr), proc(nullptr) {}
    Variant(double num) : type(Number), num(num), env(nullptr), proc(nullptr) {}
    Variant(proc_type proc) : type(Proc), num(0), env(nullptr), proc(proc) {}

    // Métodos
    std::string to_string() const;
    std::string to_json_string() const;
    static Variant from_json_string(const std::string& json_str);
    static Variant parse_json(const json& job);
};

// Implementación de to_string
std::string Variant::to_string() const {
    switch (type) {
        case Symbol:
        case Cadena:
            return val;
        case Number:
            return std::to_string(num);
        case List: {
            std::ostringstream oss;
            oss << "( ";
            for (const auto& elem : list) {
                oss << elem.to_string() << " ";
            }
            oss << ")";
            return oss.str();
        }
        case Proc:
            return "<procedure>";
        case Lambda:
            return "<lambda>";
        default:
            throw std::runtime_error("Tipo desconocido en to_string");
    }
}

// Implementación de to_json_string
std::string Variant::to_json_string() const {
    switch (type) {
        case Symbol:
        case Cadena:
            return "\"" + val + "\"";
        case Number:
            return std::to_string(num);
        case List: {
            json j_array = json::array();
            for (const auto& elem : list) {
                j_array.push_back(json::parse(elem.to_json_string()));
            }
            return j_array.dump();
        }
        case Proc:
        case Lambda:
            return "\"<function>\"";
        default:
            throw std::runtime_error("Tipo desconocido en to_json_string");
    }
}

// Implementación de from_json_string
Variant Variant::from_json_string(const std::string& json_str) {
    json parsed_json = json::parse(json_str);
    return parse_json(parsed_json);
}

// Implementación de parse_json
Variant Variant::parse_json(const json& job) {
    if (job.is_string()) {
        return Variant(Cadena, job.get<std::string>());
    } else if (job.is_number()) {
        return Variant(job.get<double>());
    } else if (job.is_array()) {
        Variant var(List);
        for (const auto& elem : job) {
            var.list.push_back(parse_json(elem));
        }
        return var;
    } else {
        throw std::runtime_error("Tipo no soportado en JSON");
    }
}

// Ejemplo de uso
int main() {
    // Crear una instancia de Variant
    Variant v1(Symbol, "hello");
    Variant v2(42.0);
    Variant v3(List);
    v3.list.push_back(v1);
    v3.list.push_back(v2);

    // Convertir a JSON
    std::cout << v3.to_json_string() << std::endl;

    // Parsear desde JSON
    std::string json_input = "[\"hello\", 42]";
    Variant parsed = Variant::from_json_string(json_input);
    std::cout << parsed.to_string() << std::endl;

    return 0;
}
