// -*- C++ -*-
// AID-GENERATED
// =========================================================================
// This class was generated by AID - Abstract Interface Definition          
// DO NOT MODIFY, but use the org.freehep.aid.Aid utility to regenerate it. 
// =========================================================================
#ifndef AIDA_ITUPLEFACTORY_H
#define AIDA_ITUPLEFACTORY_H 1

//  This file is part of the AIDA library
//  Copyright (C) 2002 by the AIDA team.  All rights reserved.
//  This library is free software and under the terms of the
//  GNU Library General Public License described in the LGPL.txt

#include <string>
#include <vector>

namespace AIDA {

class IEvaluator;
class IFilter;
class ITuple;

/**
 * A factory for creating ITuples.
 *
 * @author The AIDA team (http://aida.freehep.org/)
 */
 
class ITupleFactory {

public: 
    /// Destructor.
    virtual ~ITupleFactory() { /* nop */; }

    /**
     * Creates an NTuple
     * @param path        The path of the created ITuple. The path can either be a relative or full path.
     *                    ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                    All the directories in the path must exist. The characther `/` cannot be used
     *                    in names; it is only used to delimit directories within paths.
     * @param title       The title of the n-tuple
     * @param columnNames The names of the columns
     * @param columnType  The types of  the columns
     * @param options     NTuple options (currently undefined)
     *
     */
  virtual ITuple * create(const std::string & path, const std::string & title, const std::vector<std::string>  & columnNames, const std::vector<std::string>  & columnType, const std::string & options = "") = 0;

    /**
     * Creates an NTuple
     * @param path    The path of the created ITuple. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param title   The title of the n-tuple
     * @param columns The names and types of the columns e.g. "float px, py, pz, float energy, int charge"
     * @param options NTuple options (currently undefined)
     *
     */
    virtual ITuple * create(const std::string & path, const std::string & title, const std::string & columns, const std::string & options = "") = 0;

    /**
     * Creates a logical chain of ITuples. All ITuples in the set must
     * have the same structure. Chained ITuple can not be filled.
     * Original n-tuple data is not copied.
     * @param path  The path of the chained ITuple. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the new n-tuple
     * @param set   The array of ITuples to chain
     *
     */
    virtual ITuple * createChained(const std::string & path, const std::string & title, const std::vector<ITuple *>  & set) = 0;

    /**
     * Creates a logical chain of ITuples. All ITuples in the set must
     * have the same structure. Chained ITuple can not be filled.
     * Original n-tuple data is not copied.
     * @param path  The path of the chained ITuple. The path can either be a relative or full path.
     *              ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *              All the directories in the path must exist. The characther `/` cannot be used
     *              in names; it is only used to delimit directories within paths.
     * @param title The title of the new n-tuple
     * @param set   The array of the names of the ITuples to chain
     *
     */
    virtual ITuple * createChained(const std::string & path, const std::string & title, const std::vector<std::string>  & set) = 0;

    /**
     * Creates a new reduced tuple (less rows) from an existing one
     * by applying a filter. Data is explicitly copied to a new n-tuple.
     * @param path   The path of the filtered ITuple. The path can either be a relative or full path.
     *               ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *               All the directories in the path must exist. The characther `/` cannot be used
     *               in names; it is only used to delimit directories within paths.
     * @param tuple  Original n-tuple
     * @param filter IFilter to be used
     *
     */
    virtual ITuple * createFiltered(const std::string & path, ITuple & tuple, IFilter & filter) = 0;

    /**
     * Creates a new reduced tuple (less rows) from an existing one
     * by applying a filter. Only subset of the variables (columns) is copied.
     * Data is explicitly copied to a new n-tuple.
     * @param path    The path of the filtered ITuple. The path can either be a relative or full path.
     *                ("/folder1/folder2/dataName" and "../folder/dataName" are valid paths).
     *                All the directories in the path must exist. The characther `/` cannot be used
     *                in names; it is only used to delimit directories within paths.
     * @param tuple   Original n-tuple
     * @param filter  IFilter to be used
     * @param columns Names of columns to for a new n-tuple
     *
     */
    virtual ITuple * createFiltered(const std::string & path, ITuple & tuple, IFilter & filter, const std::vector<std::string>  & columns) = 0;

    /**
     * Creates IFilter object given a string defining of the "cut" expression.
     * @param expression String defining of the "cut" expression.
     *
     */
    virtual IFilter * createFilter(const std::string & expression) = 0;

    /**
     * Creates a filter object given a string defining the "cut" expression.
     * Filter processes only subset of data.
     * @param expression String defining of the "cut" expression.
     * @param rowsToProcess How many rows to process
     * @param startingRow Row number where to start
     *
     */
    virtual IFilter * createFilter(const std::string & expression, int rowsToProcess, int startingRow = 0) = 0;

    /**
     * Create IEvaluator object given its expression.
     * @param expression String defining of the evaluator expression.
     *
     */
    virtual IEvaluator * createEvaluator(const std::string & expression) = 0;
}; // class
} // namespace AIDA
#endif /* ifndef AIDA_ITUPLEFACTORY_H */
