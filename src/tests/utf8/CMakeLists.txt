# UTF-8 corpora (one ddc_simple call per query, each with its own canon file):
#  - Russian: morphology via cp1251 inside (lemma expansion, jo -> je, regex on Cyrillic);
#    characters outside cp1251 are dropped by the graphematics (λόγος is not found)
#  - Generic: raw UTF-8, e.g. historical German with long s (no morphology, words are not split)
macro (ddc_utf8_test lang)
    set (dir ${CMAKE_BINARY_DIR}/tests/utf8/${lang})
    add_test(
            NAME utf8_${lang}_copy
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/utf8/${lang}  ${dir}
    )
    add_test(
            NAME utf8_${lang}_index
            COMMAND ddc_index corpus.con
            WORKING_DIRECTORY  ${dir}
    )
    set (n 0)
    foreach (q ${ARGN})
        math (EXPR n "${n} + 1")
        add_test(
                NAME utf8_${lang}_query${n}
                COMMAND ddc_simple corpus.con "${q}" result${n}.html -ResultFormat html
                WORKING_DIRECTORY  ${dir}
        )
        add_test(
                NAME utf8_${lang}_diff${n}
                COMMAND ${CMAKE_COMMAND} -E compare_files result${n}.html canon${n}.html
                WORKING_DIRECTORY  ${dir}
        )
    endforeach ()
endmacro(ddc_utf8_test)

ddc_utf8_test (Russian "рама" "мыть" "ёлка" "/^ёлк|^елк/" "λόγος")
ddc_utf8_test (Generic "Waſſer" "Kaiſer" "Deꝛ" "/^ſ/" "Fluß")
