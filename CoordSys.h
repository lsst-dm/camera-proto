// -*- lsst-c++ -*-

/**
 * Base class for coordinate system keys used in in TransformRegistry
 *
 * Each coordinate system must have a unique name. Hashing and equality testing are based on this name.
 */
class CoordSys {
public:
    explicit CoordSys( std::string &name ) : _name(name) {}
    ~CoordSys() {}

    /**
     * Return a copy
     */
    CONST_PTR(CoordSys) clone() const { return boost::make_shared<CoordSys>(_name); };

    /**
     * Get name as <className>(arg1, arg2...)
     *
     * The name must be unique for a unique coordinate system,
     * since it is used by getHash operator== and other operators.
     */
    std::string getName() { return _name; };

    /** get a hash; allows use in std::unordered_map */
    size_t getHash() const {
        return hash(_name());
    }

    /** equals operator; based on name */
    bool operator==(CoordSys &rhs) const {
        return _name() == rhs._name();
    }

    /** not equals operator; based on name */
    bool operator!=(CoordSys &rhs) const {
        return _name() != rhs._name();
    }

    /** less-than operator; based on name; allows use in std::map */
    bool operator<(CoordSys.rhs) const {
        return _name() < rhs._name();
    }
public:
    std::string _name;
};

namespace std {
    /** add hash<CoordSys>(CoordSys) to std namespace
     *
     * this allows CoordSys to be used as a key in unordered_map
     * without specifying the hash template parameter
     */
    template <> struct hash<CoordSys> {
        size_t operator()(const CoordSys & x) const {
                return CoordSys.getHash();
        }
    };
}
