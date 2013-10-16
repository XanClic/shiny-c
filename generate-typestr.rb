#!/usr/bin/env ruby
# coding: utf-8

levels = 4


class Array
    def powerset
        inject([[]]) do |c, y|
            c.inject([]) do |r, i|
                r + [i, i + [y]]
            end
        end
    end
end


types = {
    'char' => 'c',
    'signed char' => 'a',
    'unsigned char' => 'h',
    'short' => 's',
    'unsigned short' => 't',
    'int' => 'i',
    'unsigned' => 'j',
    'long' => 'l',
    'unsigned long' => 'm',
    'long long' => 'x',
    'unsigned long long' => 'y',
    'float' => 'f',
    'double' => 'd',
    'long double' => 'e',
    'void' => 'v'
}

qualifiers = {
    'const' => 'K',
    'volatile' => 'V'
}


puts <<-EOS
#ifndef REFLECTION_TYPESTR_H
#define REFLECTION_TYPESTR_H
#
#define __typestr_test(t1, t2, n) \\
    __builtin_choose_expr(__builtin_types_compatible_p(t1, t2), n,

#define __typestr1(type, ts, sp) \\
EOS

qualifiers.keys.powerset.each do |qs|
    types.each do |type, tsym|
        puts "    __typestr_test(type, #{qs.map { |q| "#{q} " }.join}#{type} ts, sp \"#{qs.map { |q| qualifiers[q] }.join}#{tsym}\") \\"
    end
end

puts "    0#{''.ljust(types.length * 2**qualifiers.length, ')')}"


puts <<-EOS

#define __resolv_test(t1, t2) \\
    __builtin_choose_expr(__builtin_types_compatible_p(t1, t2), 1,

#define __resolvable1(type, ts) \\
EOS

qualifiers.keys.powerset.each do |qs|
    types.each_key do |type|
        puts "    __resolv_test(type, #{qs.map { |q| "#{q} " }.join}#{type} ts) \\"
    end
end

puts "    0#{''.ljust(types.length * 2**qualifiers.length, ')')}"


2.upto(levels) do |i|
    puts <<-EOS

#define __typestr#{i}(type, ts, sp) \\
    __builtin_choose_expr(__resolvable#{i - 1}(type, ts), __typestr#{i - 1}(type, ts, sp), \\
    __builtin_choose_expr(__resolvable#{i - 1}(type, ts const *), __typestr#{i - 1}(type, ts const *, "PK" sp), \\
    __builtin_choose_expr(__resolvable#{i - 1}(type, ts volatile *), __typestr#{i - 1}(type, ts volatile *, "PV" sp), \\
    __typestr#{i - 1}(type, ts *, "P" sp))))

#define __resolvable#{i}(type, ts) \\
    (__resolvable#{i - 1}(type, ts) | \\
     __resolvable#{i - 1}(type, ts const *) | \\
     __resolvable#{i - 1}(type, ts volatile *) | \\
     __resolvable#{i - 1}(type, ts *))
EOS
end


puts <<-EOS

#define typestr(type) __typestr#{levels}(type,,)
#define resolvable_to_typestr(type) __resolvable#{levels}(type,)

#endif
EOS
