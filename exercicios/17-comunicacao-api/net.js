const request = require("request");
const fs = require('fs');
const path = require('path');
const configuracao = require("./config");
const api = configuracao.api;
const nomeArquivo = configuracao.nomeArquivo;

/**
 * Atualiza informação do sensor
 * @param {number} id Id do Sensor
 * @param {object} dados dados a atualizar
 * @param {function} callback função de retorno
 */
function atualizar(id, dados, callback) {
    const endpointUpdateSensor = api + "/api/Sensor/" + id;
    request.put(endpointUpdateSensor, {
        json: true,
        body: dados
    }, function(error, res, body) {
        callback(error, body);
    });
}

function obterId(callback) {
    // ler arquivo ./id
    fs.readFile(nomeArquivo, function(error, data) {
        const id = data.toString();
        if(error || !id) {
            // caso não exista
            // obter id via POST /api/Sensor
            console.log("arquivo não encontrado, realizando POST");
            request.post(api + "/api/Sensor", {
                json: true,
                body: {}
            }, function(error, res, body) {
                // escrever id obtido para ./id
                fs.writeFile(nomeArquivo, body.id, function(error) {
                    callback(error, body.id);
                });
            });
            return;
        }
        console.log("arquivo encontrado!");
        // caso o arquivo exista, utilizar id lido
        callback(null, parseInt(id));
    });
    
    
}

exports.atualizar = atualizar;
exports.obterId = obterId;