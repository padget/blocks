#ifndef __blocks_serializer_hpp__
#define __blocks_serializer_hpp__

#include <string>
#include <fstream>
#include <sstream>

namespace blocks
{
	template<typename format>
		struct format_traits
		{
			using type = typename format::type;
		};

	template<typename format>
		using format_type_t = typename format_traits<format>::type;

	template <typename format> 
		struct multi_inplace_writer
		{
			using type = format_type_t<format>;

			void write(
					const std::vector<type>& vs, 
					const std::string& filename)
			{
				format fmt;
				std::ofstream os(filename + ".blb");
				for (auto&& o : vs)
					os << fmt.format(o);
				os.close();
			}
		};

	template <typename command>
		struct simple_command_format
		{
			using type = command;

			const std::string format(
					const command& cmd)
			{
				auto && name = cmd.name;
				auto && nargs = cmd.args.size();

				std::map<std::string, int> defs;

				defs.insert({"add:", 0});
				defs.insert({"print:", 1});

				std::stringstream ss;
				ss << defs[name] << ' ';
				ss << nargs << ' ' << '\n';
				return ss.str();
			}
		};
}

#endif
