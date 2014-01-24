// -*- lsst-c++ -*-

namespace geom {

/**
 * Base class for coordinate system keys used in in TransformRegistry
 *
 * Each coordinate system must have a unique name. Hashing and equality testing are based on this name.
 */
class CoordSys {
public:
    explicit CoordSys( std::string const &name ) : _name(name) {}
    ~CoordSys() {}

    /**
     * Get name as <className>(arg1, arg2...)
     *
     * The name must be unique for a unique coordinate system,
     * since it is used by getHash operator== and other operators.
     */
    std::string getName() { return _name; };

    /** get a hash; allows use in std::unordered_map */
    size_t getHash() const {
        return hash(_name);
    }

    /** equals operator; based on name */
    bool operator==(CoordSys const &rhs) const {
        return _name == rhs._name;
    }

    /** not equals operator; based on name */
    bool operator!=(CoordSys const &rhs) const {
        return _name != rhs._name;
    }

    /** less-than operator; based on name; allows use in std::map */
    bool operator<(CoordSys const &rhs) const {
        return _name < rhs._name;
    }
public:
    std::string _name;
};

} // namespace geom

namespace std {
    /** add hash<CoordSys>(CoordSys) to std namespace
     *
     * this allows CoordSys to be used as a key in unordered_map
     * without specifying the hash template parameter
     */
    template <> struct hash<CoordSys> {
        size_t operator()(CoordSys const & x) const {
                return CoordSys.getHash();
        }
    };
}
