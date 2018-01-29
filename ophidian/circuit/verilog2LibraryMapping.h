#ifndef VERILOG2LIBRARYMAPPING_H
#define VERILOG2LIBRARYMAPPING_H

#include <ophidian/parser/VerilogParser.h>
#include <ophidian/circuit/LibraryMapping.h>
#include <unordered_map>

namespace ophidian
{
namespace circuit
{
void verilog2LibraryMapping(const parser::Verilog & verilog, Netlist &netlist, standard_cell::StandardCells & standardCells, circuit::LibraryMapping & libraryMapping);
} // namespace circuit
} // namespace ophidian


#endif // VERILOG2LIBRARYMAPPING_H
